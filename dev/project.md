# Memory Management Optimization in Chatbot

## Introduction

### **Purpose** 

To analyze an existing ChatBot program, which is able to discuss some memory management topics based on the content of a knowledge base. The program can be executed and works as intended. However, no advanced concepts as discussed in this course have been used. There are no smart pointers, no move semantics and not much thought has been given on ownership and on memory allocation.

### **Current State**

The chatbot works but does not utilize advanced memory management concepts like smart pointers, move semantics, or ownership allocation.

### **Chatbot Functionality**

<img src="assets/CleanShot 2024-12-23 at 19.55.13@2x.png" alt="CleanShot 2024-12-23 at 19.55.13@2x" style="zoom: 25%;" />

- The chatbot starts at a root node (`n0`) in an answer graph.
- Users can traverse through edges (e.g., `e0`, `e1`) to explore topics like pointers or memory models.
- The chatbot moves to corresponding nodes (`n1`, `n2`, etc.) and provides relevant answers.

### **Interaction Example**

- User asks about pointers → chatbot moves to `n1` → provides options like "smart pointers."
- User selects "smart pointers" → chatbot moves to `n3` → provides details about smart pointers.

### **Customization**

The chatbot's behavior can be modified by editing the structure of the `answergraph.txt` file.

### **Our task**

Use the course knowledge to optimize the ChatBot program from a memory management perspective. There is a total of five tasks to be completed.

---

## Architechture

<div style="display: flex; gap: 10px;">
    <img src="assets/CleanShot 2024-12-24 at 13.54.36@2x.png" width="30%" />
    <img src="assets/CleanShot 2024-12-24 at 13.49.10@2x.png" width="70%" />
</div>

### Overview

1. **Main Components**:
   - ChatBot App: Encapsulates the main method within WxWidgets GUI framework
   - Instead of a traditional main method, it runs in an internal simulation loop for handling keyboard/mouse events and graphics refresh
2. **GUI Structure**:
   - ChatBot Frame: Represents the main window that refreshes periodically
   - Contains two main elements:
     1. ChatBot Panel Dialog (upper section)
     2. Text input box (lower section)
3. **Core Logic**:
   - ChatLogic: Central component handling messaging between user and chatbot
   - All communication flows through ChatLogic component
   - Manages the messaging interface and response system

### ChatLogic

<img src="assets/CleanShot 2024-12-25 at 15.01.59@2x.png" alt="CleanShot 2024-12-25 at 15.01.59@2x" style="zoom:25%;" />

1. **ChatLogic Overview**:

    - **Purpose**: ChatLogic acts as the **intermediary between the GUI and the chatbot**.
    - Ownership:
        - ChatLogic owns a set of nodes (GraphNode) and edges (GraphEdge) that represent the chatbot's answer graph.
        - Nodes are constructed from an external file (`antigraph.txt`) using the `LoadAnswerGraphFromFile` method.
    - Pointers:
        - Pointer to the current node.
        - Pointer to the chatbot instance.
        - Pointer to the panel dialog (GUI).

2. **GraphNode**:

    - Structure:
        - Contains edges leading to child nodes (owned by the node).
        - Contains a handle to parent edges (not owned).
        - Stores answers that the chatbot can provide.
    - Ownership:
        - Nodes own their child edges.
        - Nodes do not own parent edges.

    <img src="assets/CleanShot 2024-12-25 at 15.00.25@2x.png" alt="CleanShot 2024-12-25 at 15.00.25@2x" style="zoom:25%;" />

3. **GraphEdge**:

    - Components:
        - Keywords: Used to determine user intent and decide the next node.
        - ID: Unique identifier for the edge.
        - Handles to parent and child nodes.

4. **ChatBot**

    - Functionality:
        - Moves between nodes in the graph.
        - Handles its own image, which is allocated on the heap.
    - Ownership Transfer:
        - When the chatbot moves from one node to another, ownership of the chatbot is transferred to the next node.
        - Move semantics ensure the chatbot's image is not lost during transitions.
    - Pointers:
        - Pointer to the current node.
        - Pointer to the root node (for resetting the chatbot).
        - Pointer to the ChatLogic instance for communication with the GUI.

5. **GUI Integration**:

    - ChatGUI:
        - Contains classes for managing the graphical user interface.
        - Handles user input and displays chatbot responses.

### Summary

```
User input --> GUI (ChatBotFrame) --> ChatLogic --> ChatBot --> Graph(Node&Edge) --> Return Response --> GUI
```

1. User input question by `ChatBotFrame`
2. `ChatLogic` send user input to `ChatBot`。
3. `ChatBot` find best match node(answer) based on graph structure(GraphNode&GraphEdge)
4. `ChatBot` move to matched node and return answer.
5. Answer pass to `ChatLogic` and send to `ChatBotPanelDialog`, display on the GUI.

---

## Knowledge base

<img src="assets/CleanShot 2024-12-23 at 19.55.13@2x.png" alt="CleanShot 2024-12-23 at 19.55.13@2x" style="zoom: 25%;" />

### **1. Node (Node)**

#### **Definition**
Nodes represent a specific answer or topic in the knowledge base. Each node contains the following information:
- **`TYPE:NODE`**: Indicates that this is a node.
- **`ID`**: A unique identifier for the node.
- **`ANSWER`**: The content or response associated with this node.

#### **Example**
```plaintext
<TYPE:NODE><ID:0><ANSWER:Welcome! My name is MemBot. You can ask me about things related to memory management in C++. Possible topics are 'pointers' and 'the C++ memory model'. What would you like to talk about?>
```
- **Node ID**: `0`
- **Answer Content**: Welcomes the user and suggests possible topics (e.g., pointers and memory model).

#### **Node Functionality**
1. **Starting Node**: `ID:0` serves as the starting point of the conversation, welcoming the user and providing initial options.
2. **Topic Nodes**: Other nodes (e.g., `ID:1` and `ID:2`) represent specific topics in memory management.
3. **Terminal Nodes**: Some nodes do not have child nodes, indicating that the topic has no further branches (e.g., `ID:3` and `ID:4`).

### **2. Edge (Edge)**

#### **Definition**
Edges represent the connections between nodes, defining the paths from one node to another. Each edge contains the following information:
- **`TYPE:EDGE`**: Indicates that this is an edge.
- **`ID`**: A unique identifier for the edge.
- **`PARENT`**: The ID of the starting node.
- **`CHILD`**: The ID of the target node.
- **`KEYWORD`**: A list of keywords associated with this edge, used to match user input.

#### **Example**
```plaintext
<TYPE:EDGE><ID:0><PARENT:0><CHILD:1><KEYWORD:pointer><KEYWORD:smart pointer>
```
- **Edge ID**: `0`
- **Parent Node**: `ID:0` (starting node).
- **Child Node**: `ID:1` (topic related to pointers).
- **Keywords**: `pointer`, `smart pointer`.

#### **Edge Functionality**
- **Navigation Path**: Defines the path from one topic to another.
- **Keyword Matching**: Determines the next node based on the user's input. For example:
  - If the user inputs "pointer," the chatbot matches the keyword `pointer` and moves to `ID:1`.

---

## Tasks overview

### Task 0 (Warm-up)
- An **intentional bug** in the student version
- Program crashes when clicking the GUI close button
- Caused by memory management issues
- Purpose: Help **familiarize with the codebase**

### Task 1: Exclusive Ownership
- Focuses on implementing **exclusive ownership** concept
- Handling object ownership relationships

### Task 2: Rule of Five Implementation
- Implement the complete **Rule of Five** for ChatBot class:
  - Copy constructor
  - Copy assignment operator
  - Move constructor
  - Move assignment operator
  - Destructor

### Task 3: Node Ownership
- Modify the nodes vector in GraphNode class
- Requires selecting appropriate **smart pointers**
- Another task focusing on exclusive ownership

### Task 4: Moving Smart Pointers
- Handle **smart pointer movement**
- Can use shared_ptr or unique_ptr
- Requires **modifying code structure and function parameters**
- Goal: Achieve minimal cost pointer movement between program parts

### Task 5: ChatBot Movement
- Implement **ChatBot movement** between nodes
- Based on move semantics implemented in Task 2
- Enable ChatBot to:
  - Move between nodes
  - Retrieve answers from current node
  - Display to user through GUI

>  These tasks revolve around modern C++ features:
>  - Smart pointers
>  - Ownership management
>  - Move semantics
>  - Rule of Five
>  - Memory management



Each task is designed to deepen understanding and practical application of these concepts.

The progression of tasks builds upon each other, starting from basic memory management to more complex movement and ownership patterns.

---

## Code Structure

### `chatgui.h` & `chatgui.cpp`
- **Main Purpose**: Implements the graphical user interface for the chatbot
- **Key Components**:
  - `ChatBotPanelDialog`: Manages dialogue display between user and chatbot
  - `ChatBotPanelDialogItem`: Represents individual dialogue items
  - `ChatBotFrame`: Main window frame for the application
  - `ChatBotApp`: Entry point containing wxWidgets main loop
- **Key Features**:
  - Contains pointer to `ChatLogic`
  - Handles user input and message display
  - Manages dialogue interface layout and styling

### `chatlogic.h` & `chatlogic.cpp`
- **Main Purpose**: Manages core logic of the chatbot
- **Data Handling**:
  - Distinguishes between owned and non-owned data handles
  - Manages vectors of `GraphNodes` and `GraphEdges`
  - Handles interaction with `ChatBot` and `PanelDialog`
- **Core Functions**:
  - Loads answer graph from file
  - Processes message sending and receiving
  - Manages graph structure memory allocation

### `graphnode.h` & `graphnode.cpp`
- **Main Purpose**: Defines structure and behavior of graph nodes
- **Data Management**:
  - Manages edge ownership (child and parent edges)
  - Stores node ID and answer list
  - Maintains association with `ChatBot`
- **Core Methods**:
  - Adding edges and tokens
  - Handling `ChatBot` movement
  - Managing node relationships

### `graphedge.h` & `graphedge.cpp`
- **Main Purpose**: Defines connections between nodes
- **Characteristics**:
  - Owns no data
  - Acts as intermediary between nodes
  - Stores keyword list for navigation

### `chatbot.h` & `chatbot.cpp`
- **Main Purpose**: Implements core chatbot behavior
- **Key Components**:
  - Manages avatar image (owned data)
  - Tracks current and root nodes
  - Implements string similarity calculation (Levenshtein distance)
- **Core Functions**:
  - Processes user messages
  - Moves through graph
  - Selects appropriate responses

​                   









