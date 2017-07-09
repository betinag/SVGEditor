# SVGEditor

SVGEditor is an application that works with Scalable Vector Graphics (SVG) files. It loads shapes from file, performs operations on them, and then saves the changes back to the disk. Lines, circles and rectangles are supported.

## Commands:
- print - Prints all shapes on the screen.
- create \<line|circle|rectangle> \<args...> - Creates a new figure.
- erase \<id> - Removes the figure with the specified id.
- translate \<vertical> \<horizontal> [id] - Translates all figures. If id is provided, translates only the figure with the specified id.
- open \<filename> - Loads the contents of a file. If the file does not exist, an empty one is created.
- save - Saves the changes back to the file from which the data was read. 
- saveas \<filename> - Saves the changes to the specified file.
- close - Closes the current file and clears the loaded information without saving the changes.
- exit - Closes the application without saving the changes.
