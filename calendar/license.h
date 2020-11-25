#ifndef LICENSE_H
#define LICENSE_H

#define MYKEY 1234343
#include <QDate>
#include <QTime>
#include "simplecrypt.h"
#pragma comment(lib, "iphlpapi.lib")
#include <stdio.h>
#include <Windows.h>
#include <Iphlpapi.h>
#include <Assert.h>
#include <QSettings>

using namespace std ;

#define REGPATH "HKEY_CURRENT_USER\\Software\\TomSoftware"
#define REGSYSPATH "HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\SystemInformation"

char* getMAC() ;
bool isLicensed() ;

#endif // LICENSE_H
