# Focus C++ OOP Version

This is the C++ console version of the Focus app, organized as a small OOP project.

## Project structure

```text
FocusCpp/
  main.cpp
  include/
    UserProfile.h
    Task.h
    Planner.h
    PomodoroTimer.h
    Alarm.h
    MathChallenge.h
    Community.h
    FocusApp.h
    InputUtils.h
  src/
    UserProfile.cpp
    Task.cpp
    Planner.cpp
    PomodoroTimer.cpp
    Alarm.cpp
    MathChallenge.cpp
    Community.cpp
    FocusApp.cpp
    InputUtils.cpp
```

## OOP concepts used

- `class`: each feature has its own class.
- `object`: `FocusApp app;` is created in `main.cpp`.
- `constructor`: default values are initialized when objects are created.
- `destructor`: every class has a destructor.
- `getter`: read private data safely.
- `setter`: update private data safely.
- `function`: menus, task logic, timers, save/load.
- `friend`: `operator<<` and `printProfileCard` access `UserProfile` private fields.
- `encapsulation`: fields are private and controlled through functions.

## Compile with Visual Studio C++

Open Developer PowerShell for Visual Studio in this folder and run:

```powershell
cl /EHsc /std:c++17 /utf-8 /Iinclude main.cpp src\*.cpp /Fe:Focus.exe
```

Then run:

```powershell
.\Focus.exe
```

## Compile with g++

```bash
g++ -std=c++17 -Iinclude main.cpp src/*.cpp -o Focus
./Focus
```
