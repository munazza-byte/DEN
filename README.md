## DEN INTERNSHIP TASKS AND PROJECTS OVERVIEW
This repository showcases the projects and tasks undertaken during my six-week internship at Digital Empowerment Network, with a focus on implementing various systems and tools in C++.
### TASK 1: 
### *OBJECTIVE*:
Develop a Weather Forecast and Historical Data System that manages locations, weather variables, and historical data, with capabilities for fetching, displaying, and exporting weather information.
+ *DESCRIPTION*:
Created a comprehensive tool in C++ for weather forecasting and historical data retrieval.
Integrated API functionality to fetch current weather conditions and historical weather data for various locations.
Employed libcurl for API interactions and nlohmann/json for JSON data processing.
Provided features for defining weather variables, managing locations, and exporting data in both CSV and JSON formats.
+ *TECHNOLOGIES USED*: C++, libcurl, nlohmann/json, fstream, API
+ *OUTCOME*: Enabled accurate weather forecasting, efficient data export, and an intuitive interface for managing weather variables and locations.

### TASK 2:  Contacts Handling  System.
### *OBJECTIVE*:
Develop a Contact Handling System that manages a contact list, allowing users to add, remove, and display contacts interactively.
+ *DESCRIPTION*:
Created a simple Contact Handling System in C++ that allows users to manage a contact list.
Integrated functionality to add new contacts, remove existing ones, and display the entire list of contacts.
Employed a vector of Contact objects to store and manage the contact list efficiently.
Provided a menu-driven interface for the user to interact with the system.
Handled basic input validation and error messages for incorrect choices.
+ *TECHNOLOGIES USED*:C++, vector, I/O streams (iostream).
+ *OUTCOME*:Enabled efficient management of a contact list through a user-friendly interface, facilitating basic operations like adding, removing, and displaying contacts.

### TASK 3:  File Compression and Decompression System
### OBJECTIVE:
Developed a system that allows users to compress and decompress text files using Run-Length Encoding (RLE) algorithm, while ensuring file format validation and user-friendly interaction.
+ DESCRIPTION:
Built a simple file handling system in C++ that facilitates file compression and decompression using RLE. The system allows users to read text files, compress their contents, and store the compressed data in a new file. It also enables the reverse operation by decoding compressed files back to their original content. Incorporated functions for reading from and writing to files, encoding and decoding the string data using RLE, and validating file extensions to ensure correct formats are used. Provided a menu-driven interface that offers users the options to compress, decompress, or exit the program. Handled invalid user inputs using a custom exception class and ensured proper file operations through input validation.
+ TECHNOLOGIES USED: C++, file handling (fstream), string manipulation, Run-Length Encoding (RLE), input validation (custom exception handling).
+ OUTCOME: Successfully implemented a system that efficiently compresses and decompresses text files while providing a user-friendly interface and robust error handling, ensuring smooth interaction for users.

### TASK 4:  Multi-Threaded Web Server
### OBJECTIVE:
Developed a simple HTTP server in C++ that listens for client connections, handles incoming GET requests, and serves an HTML file to the client.
+ DESCRIPTION:
Built an HTTP server using socket programming in C++ that listens for incoming client connections, processes basic GET requests, and serves an HTML file (index.html). The system utilizes threading to handle multiple client connections concurrently. Implemented classes to represent generic HTTP requests and specialized GET requests, ensuring a modular approach. The server uses the HttpServer class to manage socket creation, binding, and listening, with a dedicated handleClient method for processing requests. The response includes an HTTP 200 OK status and serves the contents of index.html to the client. Included a simple menu-driven interface that allows users to start the server on a specified port or exit the program. Added functionalities to read from HTML files, respond to client requests, and manage threads, along with proper socket cleanup in the destructor. Basic validation for incoming requests and proper response formatting are provided.
+ TECHNOLOGIES USED: C++, socket programming, threading, file handling (fstream), string manipulation.
+ OUTCOME: Successfully implemented a HTTP server that serves an HTML file to clients, providing a multi-threaded approach to handle concurrent requests while maintaining a user-friendly menu interface.






