# smart-campus-management-system
An advanced C++ OOP-based system for managing university operations, including student records, attendance tracking, faculty data, and a polymorphic library management module.
# 🏫 Smart Campus Management System

A comprehensive C++ application designed to streamline campus administration. This project demonstrates advanced **Object-Oriented Programming (OOP)** principles and robust file handling.

## 🌟 Key Modules
* **Student Management:** Full CRUD (Create, Read, Update, Delete) operations with persistent storage.
* **Attendance System:** Track and calculate attendance percentages for students.
* **Faculty Records:** Dedicated module for managing staff information.
* **Library Management:** A polymorphic system handling Books, Magazines, and CDs with automated fine calculation.

## 🛠️ OOP Concepts Applied
* **Inheritance:** `Student` and `Faculty` inherit from a base `Person` class.
* **Polymorphism:** Used `virtual` functions and `override` for diverse library items (`Book`, `Magazine`, `CD`).
* **Encapsulation:** Protected data members with public accessors.
* **Memory Management:** Proper use of dynamic memory allocation and `vector` cleanup.

## 🚀 Getting Started
1. **Compile:**
   ```bash
   g++ main.cpp -o campus_system
