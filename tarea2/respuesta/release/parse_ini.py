import sys

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