import ply.lex as lex

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

t_ignore                = "     "
t_KEY_ignore            = t_ignore
t_SEPARATOR_ignore      = t_ignore
t_SECTION_ignore        = t_ignore
t_DATA_ignore           = t_ignore


def t_NEWLINE(t):
    r"(\n|\r|(\r\n))"
    t.lexer.begin('INITIAL')
    return 


def t_COMMENT(t):
    r"[;|\#].*"
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