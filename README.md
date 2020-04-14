# Computer-System
- Custom assembly instruction simulator
- Created with Visual Studio 2019 version 16.5.3, Waffle, and ImGui
 ![Main Window](https://github.com/Ownfos/Computer-System/blob/master/main%20window.png)


## Dependencies:
 - Waffle Binary(https://github.com/Ownfos/Waffle)
 - ImGui(https://github.com/ocornut/imgui)
 - fmt(https://github.com/fmtlib/fmt)
     
## Description
 - This project allows you to create custom assembly instruction and simulate executing it
 - By default, five instructions (Move, Jump, Add, Load, Store) are implemented in main.cpp as example
 - If you wish to add your own instruction, inherit either UnaryInstruction or BinaryInstruction
   Of course, inheriting Instruction (the base virtual class) and implementing everything manually is also valid choice
 ![Single Operand Instruction](https://github.com/Ownfos/Computer-System/blob/master/unary%20instruction%20example.png)
 ![Double Operand Instruction](https://github.com/Ownfos/Computer-System/blob/master/binary%20instruction%20example.png)
 - After implementing your instruction class, all you have to do is change the initial memory content\
   or provide a prototype in main function\
 ![Main Function](https://github.com/Ownfos/Computer-System/blob/master/main%20function.png)
 - After executing the program, you can dynamically change the content of memory or registers
   by right-clicking over them. Popup menu will allow you to set either a value or an instruction.
 ![Main Function](https://github.com/Ownfos/Computer-System/blob/master/popup.png)
 - Press spacebar to execute next instruction (which is shown in yellow text)
