# Focus C++ Foundation

Focus is a C++17 console-based foundation for a productivity application designed around personal focus, daily organization, weekly planning, alarms, Pomodoro sessions, and a study-community entry point.

This repository contains the core object-oriented prototype. It models the business logic and user flow of the Focus app before the same concepts are moved into a native Android application through an Android UI layer and an NDK/JNI bridge.

The project is intentionally simple, local, and portable. It does not depend on a database server, web framework, CDN, online fonts, cloud APIs, or internet-hosted UI assets.

## Purpose

The goal of this project is to define the core behavior of Focus in clean C++ before building the full mobile experience.

It demonstrates:

- A local user onboarding flow.
- A persistent user profile.
- Daily task creation and management.
- Date-based task filtering.
- A weekly planning overview.
- A simple day schedule view.
- Pomodoro and custom focus timers.
- Alarm creation.
- Alarm-dismissal math challenge logic.
- A Discord-style community link screen.
- Local file-based persistence.
- A coherent menu-based navigation flow.

The console interface is not the final user interface. It is the functional foundation used to prove the app structure, business rules, models, and user journey.

## Current Project Type

This repository is currently a C++ terminal application.

It is not a WebView app, not a website, and not a JavaScript project. The code is written in standard C++17 and organized with separate header and source files.

The Android version can reuse this foundation by keeping the core models and business logic in C++ and connecting them to native Android screens through JNI.

## Core Features

### Onboarding

When the app starts for the first time, it checks whether a default profile is still active. If no real profile exists yet, the app guides the user through onboarding.

The onboarding flow collects:

- Name.
- Gender.
- Date of birth.
- Country.
- Wake-up time.
- Sleep time.

The collected data is stored locally and loaded again on the next launch.

### Home

The home screen gives the user a simple overview of the day.

It displays:

- A greeting using the local profile name.
- Wake and sleep time.
- Open priority tasks.

Priority tasks are currently defined as all incomplete tasks.

### Planner

The planner contains the task-management logic.

Supported actions:

- Add a task.
- List all tasks.
- List tasks by date.
- Mark a task as completed.
- Delete a task.
- View a weekly overview.
- View a specific day schedule.

Each task has:

- Numeric ID.
- Title.
- Date.
- Optional time.
- Completion status.

The planner assigns task IDs automatically using an internal `nextId` counter.

### Weekly Overview

The weekly overview prints all stored tasks with their dates and completion state.

This is a simple foundation for a richer mobile weekly planning screen. In the future Android version, this can become a structured weekly calendar layout with grouped days, progress indicators, and task priorities.

### Day Schedule

The day schedule filters tasks by a specific date and prints the planned items for that day.

Tasks with a time are displayed with their `HH:MM` value. Tasks without a time are displayed as unscheduled.

### Focus Tools

The focus tools menu includes:

- Pomodoro quick demo.
- Custom timer.
- Deep work demo.
- Alarm creation.
- Alarm listing.
- Alarm math challenge test.

The current timers are intentionally short in demo mode so the terminal version is easy to test.

### Pomodoro Timer

The `PomodoroTimer` class stores:

- Focus duration.
- Break duration.
- Current session number.

It can run a countdown in the terminal and supports custom timer durations from 1 to 3600 seconds.

The terminal Pomodoro mode uses a 10-second demonstration instead of running a full 25-minute session.

### Alarm System

The `Alarm` class stores:

- Alarm time.
- Enabled or disabled state.

The current terminal version lets the user create and list alarms. It does not schedule real operating-system alarms. On Android, this logic should be connected to Android alarm APIs, notification permissions, foreground behavior rules, and device-specific battery restrictions.

### Math Challenge

The `MathChallenge` class generates a simple arithmetic challenge used as an alarm-dismissal concept.

It supports:

- Addition.
- Subtraction.
- Answer checking.
- Deterministic generation from a numeric seed.

This is useful for alarm dismissal because the user must interact with the app instead of passively closing the alarm.

### Community

The community module displays a Discord invite link.

In the terminal version, the user must copy the link manually. In the Android version, this can become a native screen with an external browser intent.

### Profile

The profile menu allows the user to view and edit local profile settings.

Supported actions:

- Edit name.
- Edit country.
- Edit date of birth.
- Edit wake and sleep time.
- Toggle dark mode.
- Toggle notifications.
- Reset local app data.

The profile is printed through a friend function, demonstrating controlled access to private class data.

## Application Flow

The main flow is progressive and connected.

```text
main.cpp
  -> creates FocusApp
  -> FocusApp loads local data
  -> splash screen
  -> onboarding if needed
  -> main menu
     -> home
     -> planner
     -> focus tools
     -> community
     -> profile
  -> save on changes and exit
```

The project avoids disconnected screens. Every feature is reachable through the main application controller, and each menu returns to the previous level instead of behaving like a separate isolated program.

## Project Structure

```text
FocusCpp/
  main.cpp
  README.md
  run_focus_terminal.bat
  Focus.exe

  include/
    Alarm.h
    Community.h
    FocusApp.h
    InputUtils.h
    MathChallenge.h
    Planner.h
    PomodoroTimer.h
    Task.h
    UserProfile.h

  src/
    Alarm.cpp
    Community.cpp
    FocusApp.cpp
    InputUtils.cpp
    MathChallenge.cpp
    Planner.cpp
    PomodoroTimer.cpp
    Task.cpp
    UserProfile.cpp
```

## Main Classes

### `FocusApp`

The central application coordinator.

Responsibilities:

- Load saved data.
- Show the splash screen.
- Run onboarding when needed.
- Display the main menu.
- Route the user to each feature area.
- Save data after important changes.
- Hold the main app objects together.

It owns:

- `UserProfile`
- `Planner`
- `PomodoroTimer`
- `vector<Alarm>`
- `Community`

### `UserProfile`

Represents the local user.

Stores:

- Name.
- Gender.
- Date of birth.
- Country.
- Wake-up time.
- Sleep time.
- Dark mode preference.
- Notification preference.

The class uses private fields, public getters and setters, constructors, and friend functions for formatted output.

### `Task`

Represents a single planner item.

Stores:

- ID.
- Title.
- Date.
- Optional time.
- Completion state.

The class supports formatted output through `operator<<`.

### `Planner`

Manages a collection of tasks.

Responsibilities:

- Add tasks.
- Complete tasks.
- Delete tasks.
- Filter tasks by date.
- Return incomplete priority tasks.
- Store and restore the next task ID.

### `PomodoroTimer`

Contains focus timer behavior.

Responsibilities:

- Store focus and break durations.
- Track the current session.
- Run a countdown.
- Start a quick demo.
- Start a custom timer.

### `Alarm`

Represents alarm configuration.

Stores:

- Alarm time.
- Enabled state.

### `MathChallenge`

Generates and checks simple arithmetic challenges for alarm dismissal.

### `Community`

Displays the community invite link.

### `InputUtils`

Contains reusable terminal input validation helpers.

It validates:

- Numeric menu choices.
- Required names.
- Required text.
- Dates in `YYYY-MM-DD` format.
- Times in `HH:MM` format.
- Optional times.

## Data Persistence

The app stores local data in:

```text
focus_data.txt
```

This file is created in the same folder where the executable runs.

The save file contains:

- Profile data.
- Task data.
- Next task ID.
- Alarm data.

The current format is simple plain text. It is easy to inspect and debug, but it is not encrypted and not designed for sensitive production data.

## Save Format Overview

The file is organized with markers:

```text
PROFILE
...
TASKS <nextId> <taskCount>
...
ALARMS <alarmCount>
...
```

Tasks and alarms use `|` as a field separator.

This format is acceptable for a learning prototype. For a production Android app, a more robust storage layer should be considered, such as SQLite, Room on the Kotlin side, or a structured C++ serialization format if the core remains fully native.

## Input Validation

The terminal app includes practical validation instead of accepting raw input blindly.

Validation rules include:

- Menu numbers must be within the allowed range.
- Names must contain at least two useful characters.
- Names cannot contain numbers.
- Task titles cannot be only numbers.
- Dates must use `YYYY-MM-DD`.
- Date values are checked for valid month and day ranges.
- Leap years are handled.
- Times must use `HH:MM`.
- Time values must be in the 24-hour range.

This is important because the same validation rules can later be reused or mirrored in the Android UI.

## Object-Oriented Concepts Used

This project demonstrates several core C++ OOP concepts:

- Classes.
- Objects.
- Constructors.
- Destructors.
- Encapsulation.
- Getters.
- Setters.
- Friend functions.
- Operator overloading.
- Composition.
- Separation between declarations and implementation.

Examples:

- `FocusApp app;` creates the main application object.
- `FocusApp` composes the main feature classes.
- `Task` overloads `operator<<` for clean printing.
- `UserProfile` uses a friend function to print a profile card.
- Private fields are accessed through controlled public methods.

## Build Requirements

You need one of the following:

- Microsoft Visual C++ compiler from Visual Studio Build Tools.
- `g++` with C++17 support.

The code uses standard C++17 and does not require third-party libraries.

## Build with Visual Studio C++

Open Developer PowerShell for Visual Studio in the project folder and run:

```powershell
cl /EHsc /std:c++17 /utf-8 /Iinclude main.cpp src\*.cpp /Fe:Focus.exe
```

Then run:

```powershell
.\Focus.exe
```

## Build with g++

On Windows with MinGW or on a Unix-like environment:

```bash
g++ -std=c++17 -Iinclude main.cpp src/*.cpp -o Focus
./Focus
```

On Windows, you can build an `.exe` with:

```powershell
g++ -std=c++17 -Iinclude main.cpp src\*.cpp -o Focus.exe
.\Focus.exe
```

## Run with the Batch File

Windows users can run:

```text
run_focus_terminal.bat
```

The batch file:

- Opens the project folder.
- Runs `Focus.exe` if it already exists.
- Tries to compile with `cl` if available.
- Tries to compile with `g++` if available.
- Prints a compiler message if no supported compiler is found.

## Typical User Journey

1. Start the app.
2. Complete onboarding.
3. Open the planner.
4. Add tasks for specific dates.
5. Return home to see open priority tasks.
6. Use the focus tools to run a timer.
7. Add an alarm.
8. Test the alarm math challenge.
9. Edit profile preferences.
10. Exit and relaunch to confirm local data is saved.

## Current Limitations

This repository is a C++ foundation, not a complete production mobile application.

Known limitations:

- The UI is terminal-based.
- Timers block the terminal while counting down.
- Alarms are stored but not scheduled through the operating system.
- There is no real Android notification integration in this repository.
- The Discord link is printed instead of opened automatically.
- The save file is plain text and not encrypted.
- There is no automated test suite yet.
- Weekly overview does not group by actual calendar week.
- Priority tasks are currently all incomplete tasks, without ranking or due-date urgency.
- Date and time values are validated, but there is no timezone logic.

These limitations are normal for the current stage. The project is best understood as a clean logic prototype and C++ base layer.

## Recommended Next Improvements

Strong next steps:

- Add automated unit tests for `Planner`, `Task`, `UserProfile`, `MathChallenge`, and input validation.
- Replace plain-text persistence with a safer structured format.
- Add task priority levels.
- Add task categories.
- Add recurring task logic.
- Add calendar-week grouping.
- Add overdue task detection.
- Add alarm enable and disable editing.
- Add delete alarm support.
- Separate terminal UI from core business logic more strictly.
- Create a JNI-friendly interface layer for Android.
- Add Android-specific alarm scheduling in the native mobile app.

## Android Architecture Direction

For the Android version, the recommended architecture is:

```text
Android native UI
  -> Kotlin or Java screens
  -> Navigation and permissions
  -> AlarmManager and notifications
  -> Local Android storage
  -> JNI bridge
  -> C++17 core logic
```

The C++ layer should keep the core rules:

- User profile model.
- Task model.
- Planner logic.
- Calendar rules.
- Alarm challenge generation.
- Pomodoro logic.
- Local progress calculations.

The Android layer should handle:

- Activities or fragments.
- Native views.
- Navigation.
- Permissions.
- Notifications.
- Real alarm scheduling.
- Device lifecycle.
- Local storage integration.

This split keeps the business logic reusable while still delivering a proper native Android experience.

## Android Performance Notes

The mobile app should be built with low-end and mid-range Android devices in mind.

Important requirements:

- Avoid heavy startup work on the UI thread.
- Avoid blocking the first screen while C++ initializes.
- Use a proper light launch theme.
- Do not use a transparent startup background.
- Load screens progressively.
- Keep animations lightweight.
- Avoid a WebView-only implementation.
- Support both `armeabi-v7a` and `arm64-v8a`.
- Keep memory usage low.

This is especially important for older Android phones and devices with limited RAM and CPU capacity.

## Privacy and Local Data

The current app stores all data locally.

It does not send profile data, task data, alarms, or preferences to a server.

However, the current `focus_data.txt` file is plain text. Anyone with access to the project folder can read it. For a production mobile app, sensitive information should be stored through Android-appropriate local storage with proper privacy considerations.

## Testing Checklist

Before considering a build stable, manually verify:

- First launch opens onboarding.
- Profile data saves after onboarding.
- Relaunch loads the saved profile.
- Invalid names are rejected.
- Invalid dates are rejected.
- Invalid times are rejected.
- Tasks can be added.
- Tasks can be listed.
- Tasks can be filtered by date.
- Tasks can be completed.
- Tasks can be deleted.
- Weekly overview displays stored tasks.
- Day schedule displays tasks for the selected date.
- Custom timer runs for the requested duration.
- Alarm creation works.
- Alarm list displays saved alarms.
- Math challenge accepts the correct answer.
- Profile reset clears local app data.
- Exiting and relaunching keeps expected saved state.

## Troubleshooting

### `cl` is not recognized

Install Visual Studio Build Tools and open Developer PowerShell for Visual Studio before running the compile command.

### `g++` is not recognized

Install MinGW, MSYS2, or another C++ toolchain, then make sure the compiler is available in `PATH`.

### The app loads old data

Delete `focus_data.txt` from the executable folder, then run the app again.

### The terminal closes immediately

Run the app from PowerShell or use `run_focus_terminal.bat` so the window stays open after execution.

### Arabic or non-English names display incorrectly

Build with UTF-8 support where possible. With Microsoft C++, use:

```powershell
cl /EHsc /std:c++17 /utf-8 /Iinclude main.cpp src\*.cpp /Fe:Focus.exe
```

Terminal font and code page settings may also affect display.

## Professional Assessment

The project is a solid C++ foundation for a productivity app prototype. Its strongest points are the clear class separation, coherent menu flow, local persistence, input validation, and direct mapping between app features and C++ models.

The main weakness is that UI and business flow are still tightly coupled inside the terminal controller. Before scaling into a larger Android project, the core logic should be separated further from console input/output. That would make the C++ layer easier to test, easier to expose through JNI, and safer to reuse in a native mobile app.

## Final Project Note

Starting from this C++ foundation, we built the core base of Focus and provided it to Codex. Codex then generated an Android mobile application from this foundation, resulting in a phone app that runs on Android.
