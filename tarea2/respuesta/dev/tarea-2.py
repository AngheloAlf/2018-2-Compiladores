import ply.lex as lex
import sys
import json

tokens = (
   "KEY",
   "SEPARATOR",
   "VALUE",
   "COMMENT",
   "NEWLINE",
   "SECTION",
   "DATA", 
   "END",
)

states = (
    ("KEY", "exclusive"),
    ("SEPARATOR", "exclusive"),
    ("SECTION", "exclusive"),
    ("DATA", "exclusive"),
)

t_ignore                = " 	"
t_KEY_ignore            = t_ignore
t_SEPARATOR_ignore      = t_ignore
t_SECTION_ignore        = t_ignore
t_DATA_ignore           = t_ignore

def t_error(t):
    print('Lexical error: "' + str(t.value) + '" in line ' + str(t.lineno))
    return

def t_NEWLINE(t):
    r"(\n|\r|(\r\n))"
    t.lexer.begin('INITIAL')
    return 


def t_COMMENT(t):
    r"[;|\#].*"
    return 

def t_KEY_error(t):
    print('KEY Lexical error: "' + str(t.value) + '" in line ' + str(t.lineno))
    return 

def t_KEY(t):
    r"[^=;\#\[\]\s]+"
    t.lexer.begin("KEY")
    t.value = t.value.lower()
    return t

def t_KEY_COMMENT(t):
    r"[ \t]*[;|\#].*"
    t.lexer.begin("INITIAL")
    return 

def t_KEY_NEWLINE(t):
    r"[ \t]*(\n|\r|(\r\n))"
    t.lexer.begin("INITIAL")
    return 

def t_KEY_SEPARATOR(t):
    r"[ \t]*=[ \t]*"
    t.value = t.value.strip().lower()
    t.lexer.begin("SEPARATOR")
    return t

def t_SEPARATOR_error(t):
    print('SEPARATOR Lexical error: "' + str(t.value) + '" in line ' + str(t.lineno))
    return 

def t_SEPARATOR_VALUE(t):
    r"[^;\#\n\r]+"
    t.value = t.value.strip()
    aux = t.value.lower()
    if(t.value.isdigit()):
        t.value = int(t.value)
    elif(aux in ("false", "true")):
        t.value = aux == "true"
    t.lexer.begin("INITIAL")
    return t


def t_SECTION(t):
    r"\["
    t.lexer.begin("SECTION")
    return t

def t_SECTION_DATA(t):
    r"[a-zA-Z\d\-\._]+"
    t.lexer.begin("DATA")
    return t

def t_DATA_END(t):
    r"\]"
    t.lexer.begin("INITIAL")
    return t

def t_DATA_error(t):
    print('DATA Lexical error: "' + str(t.value) + '" in line ' + str(t.lineno))
    return

def t_SECTION_error(t):
    print('SECTION Lexical error: "' + str(t.value) + '" in line ' + str(t.lineno))
    return 


def check_cmd():
    if(len(sys.argv) == 1):
        print("Usage: tarea2.py file.ini")
        exit(1)
    return

def getFullFile():
    check_cmd()
    fullFile = ""
    with open(sys.argv[1]) as openedFile:
        fullFile = openedFile.read()
    return fullFile

def parseIniFile(fullFile):
    lexer = lex.lex()
    lexer.input(fullFile)

    lastKey = ""
    lastSection = ""
    hashed = {lastSection: dict()}
    for tok in lexer:
        if(tok.type == "KEY"):
            lastKey = tok.value
            if(lastKey not in hashed):
                hashed[lastSection][lastKey] = None
        
        if(tok.type == "VALUE"):
            hashed[lastSection][lastKey] = tok.value

        if(tok.type == "DATA"):
            lastSection = tok.value
            hashed[lastSection] = dict()
    if(len(hashed[""]) == 0):
        del hashed[""]
    return hashed


def main():
    ini = parseIniFile(getFullFile())
    print(json.dumps(ini, ensure_ascii=False, indent=4))
    return

if __name__ == "__main__":
    main()
