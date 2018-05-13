<pre>
 ___      ___  ___  ___  ___________  _______   _______   ___      ___
|"  \    /"  ||"  \/"  |("     _   ")/"     "| /"      \ |"  \    /"  |
 \   \  //   | \   \  /  )__/  \\__/(: ______)|:        | \   \  //   |
 /\\  \/.    |  \\  \/      \\_ /    \/    |  |_____/   ) /\\  \/.    |
|: \.        |  /   /       |.  |    // ___)_  //      / |: \.        |
|.  \    /:  | /   /        \:  |   (:      "||:  __   \ |.  \    /:  |
|___|\__/|___||___/          \__|    \_______)|__|  \___)|___|\__/|___|

</pre>

# Purpose

I prefer simplicity and customizability instead of complexity and ease of use.
That being said I didn't feel as though there were enough simple easy-to-use
text editors available. So I decided to build this one. I'm attempting to make
it as simple as possible and configurable so that anyone who has a small amount
of C knowledge can add features that they'd like.

For now running myTerm is as simple as running `make` in the base directory. You will need both the `curses` library and the `menu` library. Both of these should already be installed on most UNIX systems by default.


### TO-DO
- [ ] Fix segmentation fault on Mac OS X.
- [ ] Add modules to search directories
- [ ] Search user directories for auto-completion of code using user libraries
- [ ] Fix Makefile so it'll add the correct library for `curses`
- [ ] Add line numbering
- [ ] Add syntax highlighting
- [x] Add popup menu for auto-completion after (.)
