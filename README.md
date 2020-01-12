# NeuroLab

I've just uploaded the Qt files.
To those who want to help program the GUI:
- Download Qt and just load the project NeuroLab.pro
- It is better if you use the design tool by clicking on the "MainWindow.ui" file.
- So it doesn't matter if you type every single position and parameters of buttons, tabs and other things, or just use the design tool.
- The "MainWindow.cpp" includes the (normal) header "MainWindow.h" AND "ui-MainWindow.h", which is generated from the design tool(the .ui file).
- You can see the generated files in the Folder "build-neurolab ...".
- Or you can generate the header file yourself, by using the UIC tool from Qt. Yo might need to update it.
- i. e. " uic -i MainWindow.ui -o MyHeader.h " . I found it usefull, to see how Qt uses functoins to desing the main window. Ofcourse you need to type the full path of the files, or open Terminal in the same folder.

Merry Christmas.


Update (Movidius): 
a great intro from openvino
https://docs.openvinotoolkit.org/2018_R5/_docs_IE_DG_Integrate_with_customer_application_new_API.html

Update (Controllers loop):
I had some problems connecting Master<->Viewcontroller<->GUI. I have been doing a loop of includes. Each class includes the other, which needs infinte memory.
Solution: first answer:
https://stackoverflow.com/questions/4964482/how-to-create-two-classes-in-c-which-use-each-other-as-data
