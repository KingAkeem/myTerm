 <pre align="center">
         tttt                                                  iiii  
      ttt:::t                                                 i::::i 
      t:::::t                                                  iiii  
      t:::::t                                                        
ttttttt:::::ttttttt        eeeeeeeeeeee    nnnn  nnnnnnnn    iiiiiii 
t:::::::::::::::::t      ee::::::::::::ee  n:::nn::::::::nn  i:::::i 
t:::::::::::::::::t     e::::::eeeee:::::een::::::::::::::nn  i::::i 
tttttt:::::::tttttt    e::::::e     e:::::enn:::::::::::::::n i::::i 
      t:::::t          e:::::::eeeee::::::e  n:::::nnnn:::::n i::::i 
      t:::::t          e:::::::::::::::::e   n::::n    n::::n i::::i 
      t:::::t          e::::::eeeeeeeeeee    n::::n    n::::n i::::i 
      t:::::t    tttttte:::::::e             n::::n    n::::n i::::i 
      t::::::tttt:::::te::::::::e            n::::n    n::::ni::::::i
      tt::::::::::::::t e::::::::eeeeeeee    n::::n    n::::ni::::::i
        tt:::::::::::tt  ee:::::::::::::e    n::::n    n::::ni::::::i
          ttttttttttt      eeeeeeeeeeeeee    nnnnnn    nnnnnniiiiiiii
</pre>

# Purpose

I prefer simplicity and customizability instead of complexity and ease of use.
That being said I didn't feel as though there were enough simple easy-to-use
text editors available. So I decided to build this one. I'm attempting to make
it as simple as possible and configurable so that anyone who has a small amount
of C knowledge can add features that they'd like.

For now running teni is as simple as running `make` in the base directory. You will need both the `curses` library and the `menu` library. Both of these should already be installed on most UNIX systems by default.
[![demo](https://asciinema.org/a/tKl1TaUphMlWSgMmK3PWn8MaU.png)](https://asciinema.org/a/tKl1TaUphMlWSgMmK3PWn8MaU?autoplay=1)

### TO-DO
- [ ] Fix segmentation fault on Mac OS X.
- [ ] Add modules to search directories
- [ ] Search user directories for auto-completion of code using user libraries
- [x] Makefile uses lldb debugger instead of gdb when using Darwin
- [ ] Add line numbering
- [ ] Add syntax highlighting
- [x] Add popup menu for auto-completion after (.)
- [x] Select highlighted item from popup menu
