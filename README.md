# LazyMe
# Forked from YY at https://github.com/YYBer/LazyMe

Now you can spit out classes like a true 42 machine gun!

Improved on YY's version of an automatic class constructor by reducing the amount of thing a user has to type.
Current usage will take a class name as the first argument and create an appropriate .CPP and .HPP files in your current directory.

Usage:
1. Compile:
c++ -o lazyme lazyme.cpp

2. Add the executable as an alias in terminal (example for zsh).
open your .zshrc settings file:

nano ~/.zshrc

add this line in the end of the file:

alias class='/home/user/bin/myprogram/lazyme'

apply zsh settings to your current session:

source ~/.zshrc

3. Profit!
The following one-line command will make you a class of your choice:
class myWonderfullClass

