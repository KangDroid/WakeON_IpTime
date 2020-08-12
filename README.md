WakeOnLan CLI For IPTime
==========================

Project Description
-------------------
This is Command-Line-Interface application where we can use WakeOnLan feature anywhere, with single-execution.<br>

Normally, to use wake-on-lan feature with IPTime router from outside, we always needed to open our browser, such as chrome/safari, access/login router's admin web page[The "192.168.0.1"] and select WOL Menu and turn on.<br>
Which this process is kinda tiresome[Browser Open, Acesss, Login, WOL, Close Browser] and cannot be automated.<br>
Therefore I came with solution like this project.

How to build[Build: Local, Use[Target]: Local]
-----------------------------
It is based on CMake Project, so basically, you can:
1. Clone this repository<br>
```
$ git clone https://github.com/KangDroid/WakeON_IpTime
```
2. Create build directory<br>
```
$ cd WakeON_IpTime
$ mkdir build
```
3. cd to build directory && Initiate CMake<br>
```
$ cd build
$ cmake ..
```
4. Build![Use jthread if you want to, but this project is relevantly small though :)]<br>
```
$ make
```

How to build[Build: Linux, Use[Target]: macOS]
----------------------------------------------
Basically this means cross-compiling, targeting for macOS from Linux.[Meaning Building on Linux but using for macOS]<br>
Assuming you have cross-compiler such as: [OSXCROSS](https://github.com/tpoechtrager/osxcross)
1. Clone this repository<br>
```
$ git clone https://github.com/KangDroid/WakeON_IpTime
```
2. Create build directory
```
$ cd WakeON_IpTime
$ mkdir build
```
3. cd to build directory
```
$ cd build
$ cmake ..
```
4. Initiate CMake
In this step, you need several macOS Libraries to be placed on local linux machine.<br>
List of libs:
- Boost C++ Library for macOS
- OpenSSL Library for macOS
- CPPRESTSDK Library for macOS
- ZLib Library for macOS[Needed from CPPRESTSDK]

For me, I just placed all libraries on /home/kangdroid/cross_libraries. <br>
The place where you put macOS libraries[to-be-linked] is should be passed on CMAKE_PREFIX_PATH, Also CMAKE_C_COMPILER/CMAKE_CXX_COMPILER must be defined to cross-compile on linux.<br>
<br>
For example, I have macOS libraries on /home/kangdroid/cross_libraries, C Compiler for o64-clang, C++ Compiler for o64-clang++, I can initiate CMake like this:
```
cmake .. -DCMAKE_PREFIX_PATH=/home/kangdroid/cross_libraries -DCMAKE_C_COMPILER=o64-clang -DCMAKE_CXX_COMPILER=o64-clang++
```
5. Build![Use jthread if you want to, but this project is relevantly small though :)]
```
$ make
```

The Settings
--------------
In order to this thing make work, you need to setup single-simple json file, containing Router admin page address[Typically 192.168.0.1], and mac Address, and admin ID<br>
Something like this:
```
[
    {
        "ip_address": "192.168.0.1",
        "mac_address": "zz-zz-zz-zz-zz-zz",
        "username": "kangdroid"
    }
]
```

|Field|Type|Expl|
|-----|---|-----|
|ip_address|String|IP Address or domain to router's admin page. <br>Port should be included in this field if special port specified.|
|mac_address|String|Target MAC Address, like zz-zz-zz-zz-zz-zz<br>[Where zz should be replaced with your one.]|
|username|String|Admin ID, this program will prompt password in run-time.<br> Specifying password on plan json file looks too dangerous, so I decided to get password from user by runtime input|

How to Use?
------------
This is Command-Line Application.
```
$ ./WakeOnLanIPTime --credential_info "PATH_TO_SETTING_JSON"
```

For example,
```
$ ./WakeOnLanIPTime --credential_info "/home/kangdroid/settings.json"
```

If you do not specify --credential_info, program will use default path of setting.json.[Which you might not exists.]

TODO
-----
- HELP on command line
- Multi-WOL
- Error Handling[What??]