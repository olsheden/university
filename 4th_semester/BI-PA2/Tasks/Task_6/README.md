# Task description
    The task is to design and implement a set of classes that will simulate elements in the user interface. Specifically, it is a window (CWindow), a button (CButton), a text input (CInput), a text label (CLabel) and a combobox (CComboBox).

    The task is focused on the design of classes where inheritance, polymorphism and abstract methods will be used. If these OOP resources are used rationally, the implementation is not too long. On the contrary, if you implement the design incorrectly, the code will repeat itself and the implementation file will be large.

    The proposed classes will only simulate the GUI. They will not render anything, they will only create models of user elements. The classes can therefore be used to build a model of user controls in the window, manipulate their state, and display their state in the output stream (see below). Individual8 windows and individual user elements can be identified using their numerical id, if this id is unique, then the element can be searched using this id. If the id is not unique, the control will work, but will not be searchable by that id.

    The window will respond to the position/size change. The position and size of individual control elements is specified relative to the width/height of the parent window (the size/position is therefore a decimal number in the range 0 to 1). When resizing the window, the positions and sizes of individual control elements are recalculated. During the conversion, the corresponding width (height) is multiplied by the decimal number of the position/size and the resulting decimal number is used for display.

    The interface of classes for representing controls is very similar. A constructor typically has 2 or 3 parameters. The first parameter is usually the integer id assigned to the control element. This is followed by the location information (a CRect with 4 components of type decimal that give the relative position x, y and the relative magnitudes of w and h). The last parameter is usually a string that determines the displayed content. Furthermore, all classes implementing controls must be able to appear in the output stream with the << operator, and must be able to copy themselves correctly (deep copy). The test environment usually requires only this basic functionality (ie constructor, copy and operator for output). However, your implementation will probably require another interface, which you will have to add to the classes.

    CButton
    Represents a button. The test environment only requires a constructor and an operator for output.
    CInput
    Represents text input. The last parameter of the constructor is the string that is displayed in the input box. The test environment requires a constructor, an output operator, and two other methods:
    setValue ( x ) which sets the content to the string x,
    getValue ( ) which returns the currently displayed string.
    CLabel
    Represents static text. The last parameter of the constructor is the displayed string. The test environment requires a constructor and an operator for output.
    CComboBox
    Represents a combobox. The test environment requires a constructor, an operator for output, and 3 other methods:
    add ( x ) which adds the specified string x to the menu list,
    setSelected ( x ), which sets the menu at index x as selected (the default is the selected menu at index 0),
    getSelected() which finds the index of the currently selected menu.
    CWindow
    Represents a window. The class has the following interface:
    CWindow(id, title, absPos) constructor that creates a window named title. The window will have the x,y position and w x h size set according to the specified absPos parameter. Attention, here the dimensions are absolute.
    The add( x ) method, which adds an x control.
    setPosition ( absPos ) method that changes the position/size of the window. The specified values are the absolute coordinates and the size of the window after the change. At the same time, the method ensures recalculation of the position and size of all control elements contained in the window.
    The search ( id ) method searches for the control by the specified id. If the element with the specified id does not exist in the window, the method returns nullptr. If there are multiple controls with the same id in the window, the method returns a reference to one of them (eg the first one).
    The operator << displays the contents of the window to the output stream, the format is obvious from the attached source code.
    CRect
    A helper class representing a rectangle. This class is implemented in the test environment and is also included in the attached source file. Leave it in the conditional translation block when submitting.