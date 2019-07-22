#include <windows.h>
#include <stdio.h>

int main(int argc, char *argv[]){
  char dbserver[1000];
  int dbport;
  GetPrivateProfileString("", "key1", "su ejemplito loco", dbserver, sizeof(dbserver) / sizeof(dbserver[0]), ".\\example.ini");
  printf("%s\n", dbserver);
  
  dbport = GetPrivateProfileInt("database", "port", 143, ".\\dbsettings.ini");
  // N.B. WritePrivateProfileInt() does not exist
  return 0;
}