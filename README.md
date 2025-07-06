# Car Dealership Management System

A comprehensive Object-Oriented Programming (OOP) project implementing a car dealership management system with advanced C++ features including design patterns, inheritance hierarchies, and interactive console interface.

## Project Overview

This project demonstrates a complete car dealership management system that handles vehicle inventory, client management, showroom operations, and transaction processing. Built with modern C++ practices and advanced OOP concepts.

## Key Features

### Core Functionality
- **Vehicle Management**: Add, remove, and manage different types of vehicles
- **Client Management**: Handle client information, payment history, and purchase tracking
- **Showroom Operations**: Manage multiple showrooms with vehicle inventory
- **Transaction Processing**: Complete purchase transactions with payment tracking
- **Interactive Console Menu**: User-friendly menu system for all operations

### Technical Highlights

#### Design Patterns
- **Singleton Pattern**: Centralized application management and menu system
- **Observer Pattern**: Real-time notifications for system changes
- **Factory Pattern**: Dynamic object creation with polymorphism

#### Advanced OOP Concepts
- **Three-Level Inheritance Hierarchy**: 
  - `Vehicle` (Base class)
  - `FuelVehicle` (Child class)
  - `HybridVehicle` (Grandchild class)
- **Multiple Inheritance**: Classes implementing multiple interfaces
- **Polymorphism**: Virtual functions and dynamic binding
- **Upcasting/Downcasting**: Safe type casting with `dynamic_cast`

#### Modern C++ Features
- **STL Containers**: `vector`, `list`, `map`, `set` for efficient data management
- **Exception Handling**: Custom exception classes for robust error management
- **Template Classes**: Generic programming for reusable components
- **Operator Overloading**: Custom operators for intuitive object manipulation

## Architecture

### Class Hierarchy

```
IOInterfaceVehicle    InterfaceVehicle
       |                     |
       |                     |
       +------Vehicle--------+
                 |
                 |
            FuelVehicle
                 |
                 |
           HybridVehicle
```

### Main Classes

#### Core Business Logic
- **`Vehicle`**: Base class implementing vehicle interfaces with common attributes (brand, model, year, price)
- **`FuelVehicle`**: Extends Vehicle with fuel-specific properties (fuel type, consumption)
- **`HybridVehicle`**: Extends FuelVehicle with hybrid-specific features (electric range, charging time)

#### Management Classes
- **`Showroom`**: Manages vehicle inventory and showroom operations
- **`Client`**: Handles client information and purchase history
- **`Transaction`**: Processes and records vehicle purchases

#### System Classes
- **`Singleton`**: Application controller and menu system
- **`Observer<T>`**: Abstract observer for notifications
- **`ConsoleObserver<T>`**: Console-based notification system
- **`Subject`**: Manages observer subscriptions and notifications

#### Utility Classes
- **`InfoVehicul<T>`**: Template class for detailed vehicle information
- **`MyException`**: Custom exception handling

## Getting Started

### Prerequisites
- C++17 or later
- Visual Studio 2019/2022 (Windows)
- Windows 10 SDK

### Building the Project
1. Clone the repository
2. Open `Proiect 3 POO.sln` in Visual Studio
3. Build the solution (Ctrl+Shift+B)
4. Run the executable

### Usage
The application provides an interactive menu system:

1. **Vehicle Models Management**
   - Add new vehicle models
   - View existing vehicles
   - Remove vehicles from inventory

2. **Client Management**
   - Register new clients
   - View client information
   - Track payment history

3. **Showroom Operations**
   - Create and manage showrooms
   - Add vehicles to showrooms
   - View detailed showroom information

4. **Transaction Processing**
   - Process vehicle sales
   - Record payments
   - Generate transaction history

## Technical Implementation

### Memory Management
- Smart pointer usage where applicable
- Proper object lifecycle management
- Clone pattern for object copying

### Error Handling
- Custom exception classes
- Input validation
- Graceful error recovery

### Data Structures
- Dynamic containers for scalable data storage
- Efficient search and retrieval algorithms
- Optimized memory usage

## Design Patterns Used

1. **Singleton**: Ensures single instance of application controller
2. **Observer**: Decoupled notification system
3. **Template Method**: Standardized object operations
4. **Factory**: Dynamic object creation based on type

## Features Demonstrated

### OOP Principles
- Encapsulation
- Inheritance (3-level hierarchy)
- Polymorphism
- Abstraction

### Advanced C++ Features
- Virtual functions
- Pure virtual functions
- Multiple inheritance
- Template classes
- Operator overloading
- Exception handling
- STL containers
- Dynamic casting

## Code Quality

- Consistent naming conventions
- Comprehensive error handling
- Modular design
- Efficient algorithms
- Memory-safe operations

## Project Structure

```
Car-Dealership-Management-OOP/
├── Proiect 3 POO.cpp           # Main source file
├── Proiect 3 POO.sln           # Visual Studio solution
├── Proiect 3 POO.vcxproj       # Project configuration
├── ClassDiagram.cd             # Class diagram
└── README.md                   # This file
```

## Educational Value

This project serves as an excellent demonstration of:
- Advanced OOP concepts in C++
- Design pattern implementation
- Real-world application architecture
- Modern C++ best practices
- Interactive console application development
