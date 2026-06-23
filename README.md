================================
Project: Time-Travelling File System
================================

## 1. Description
This project is a simplified, in-memory version control system inspired by Git. It manages a collection of files, each with its own version history represented as a tree. The system supports creating and modifying files, branching via a rollback mechanism, and inspecting a file's history.

The core of the project is the implementation of three fundamental data structures from scratch: a Tree to manage version history, HashMaps to provide fast lookups for files and versions, and Heaps to efficiently track system-wide analytics.

## 2. How to Compile
To compile the project, navigate to the root directory in a Linux or WSL terminal and execute the provided shell script:

~~~bash
./compile.sh
~~~

This will use g++ to compile all the necessary source files and create a single executable named "myprogram".

## 3. How to Run
After a successful compilation, run the program from the same terminal with the following command:

~~~bash
./myprogram
~~~

The program will then wait for you to input commands.

## 4. Command Reference
The following commands are supported by the system.

---
### Core File Operations
* **CREATE <filename>**
  - Description: Creates a new, empty versioned file. The root version (ID 0) is created automatically and marked as an initial snapshot.
  - Example: `CREATE report.docx`

* **READ <filename>**
  - Description: Displays the content of the currently active version of the specified file.
  - Example: `READ report.docx`

* **INSERT <filename> <content>**
  - Description: Appends the given content to the active version. If the active version is a snapshot, a new version is created as a child.
  - Example: `INSERT report.docx "This is the first sentence."`

* **UPDATE <filename> <content>**
  - Description: Replaces the content of the active version with the given content. If the active version is a snapshot, a new version is created as a child.
  - Example: `UPDATE report.docx "A whole new document."`

* **SNAPSHOT <filename> <message>**
  - Description: Marks the active version as a snapshot, making its content immutable. It stores the provided message and the current time as a snapshot timestamp.
  - Example: `SNAPSHOT report.docx "First draft complete"`

* **ROLLBACK <filename> [versionID]**
  - Description: Changes the active version. If a `versionID` is provided, it jumps to that version. If no ID is provided, it moves to the parent of the current active version.
  - Example (with ID): `ROLLBACK report.docx 2`
  - Example (to parent): `ROLLBACK report.docx`

* **HISTORY <filename>**
  - Description: Lists all snapshotted versions on the path from the current active version up to the root, in chronological (oldest to newest) order.
  - Example: `HISTORY report.docx`

---
### System-Wide Analytics
* **RECENT_FILES [num]**
  - Description: Lists the `num` most recently modified files in descending order of their last modification time. If `num` is not provided, lists all files.
  - Example (top 3): `RECENT_FILES 3`
  - Example (all): `RECENT_FILES`

* **BIGGEST_TREES [num]**
  - Description: Lists the `num` files with the highest total version count in descending order. If `num` is not provided, lists all files.
  - Example (top 5): `BIGGEST_TREES 5`
  - Example (all): `BIGGEST_TREES`

---
### Program Control
* **exit**
  - Description: Terminates the program.

## 5. Error Handling
The program handles incorrect and inconsistent input in the following ways:

* **Missing Arguments**: If a required argument (like a filename or content) is missing, an error message is displayed, and the command is ignored.
* **Extra Arguments**: 
  - For commands expecting a single-word argument (e.g., CREATE), if multiple words are given, the system uses the first word and displays a warning that the rest were ignored.
  - For commands with a fixed number of arguments (e.g., ROLLBACK with an ID), any extra input will result in an error.
* **Non-Existent Items**: Attempting to operate on a file or version ID that does not exist will result in an error message.
* **Re-Snapshotting**: If the `SNAPSHOT` command is used on a version that is already a snapshot, the command is ignored, and a message is displayed to the user informing them of this.
```eof

***

THANK YOU
