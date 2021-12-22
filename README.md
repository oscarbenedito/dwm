# Oscar's dwm fork

This is my personal fork of [dwm][dwm] (dynamic window manager), a dynamic
window manager for X.

## Requirements

In order to build dwm you need the Xlib header files. This build uses Font
Awesome icons for the status bar, make sure you have installed the correct
files.

## Installation

Edit `config.mk` to match your local setup (dwm is installed into the
`/usr/local` namespace by default).

Afterwards enter the following command to build and install dwm (if necessary as
root):

```
make clean install
```

## Running dwm

Add the following line to your `.xinitrc` to start dwm using startx:

```
exec dwm
```

In order to connect dwm to a specific display, make sure that the `DISPLAY`
environment variable is set correctly, e.g.:

```
DISPLAY=foo.bar:1 exec dwm
```

(This will start dwm on display `:1` of the host `foo.bar`.)

In order to display status info in the bar, you can do something like this in
your `.xinitrc`:

```
while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
do
	sleep 1
done &
exec dwm
```

## Configuration

The configuration of dwm is done by editing the file `config.h` and
(re)compiling the source code.

## Keyboard shortcuts

You can check the man page for dwm to learn all about it, the only thing that is
not up to date are my personal shortcuts. Here they are (although some might not
be up to date):

DWM:

| Key         | Description                                     |
| :---------- | :---------------------------------------------- |
| `j`         | Focus next window.                              |
| `k`         | Focus previous window.                          |
| `h`         | Decrease master area size.                      |
| `l`         | Increase master area size.                      |
| `,`         | Focus next screen.                              |
| `.`         | Focus previous screen.                          |
| `b`         | Toggle status bar on/off.                       |
| `q`         | Close current window.                           |
| `Space`     | Make current window the main window.            |
| `Shift`+`+` or `Shift`+`=` | Increase number of main windows. |
| `Shift`+`-` | Decrease number of main windows.                |
| `g`         | Increase gaps.                                  |
| `Shift`+`g` | Decrease gaps.                                  |
| `Shift`+`b` | Toggle gaps on/off.                             |
| `Ctrl`+`q`  | Quit dwm.                                       |
| `Tab`       | Toggles to previously selected tags.            |

Layouts:

| Key         | Description                     |
| :---------- | :------------------------------ |
| `t`         | Tiled layout (default).         |
| `Shift`+`t` | Floating layout.                |
| `Ctrl`+`t`  | Stack on bottom layout.         |
| `i`         | Monocle layout.                 |
| `Shift`+`i` | Deck layout.                    |

Utilities:

| Key              | Description                                        |
| :--------------- | :------------------------------------------------- |
| `p`              | Spawn dmenu to launch other programs.              |
| `o`              | Spawn logout menu.                                 |
| `m`              | Spawn mount/unmount drive menu.                    |
| `s`              | Screenshot (select area).                          |
| `Shift`+`s`      | Screenshot (whole screen).                         |
| `c`              | Input user and password from `pass`.               |
| `Shift`+`c`      | Input password from `pass`.                        |
| `n`              | Create temp file and copy to primary clipboard.    |
| `Shift`+`n`      | Create temp dir and copy to primary clipboard.     |
| `+` or `=`       | Increase volume (+`Shift` for smaller increments). |
| `-`              | Decrease volume (+`Shift` for smaller increments). |
| `Shift`+`Return` | Change keyboard layout.                            |

Applications:

| Key      | Description                         |
| :------- | :---------------------------------- |
| `Return` | Start terminal.                     |
| `f`      | Start Firefox.                      |
| `e`      | Start email client (Thunderbird).   |
| `x`      | Start Signal app.                   |

Tags (`n` between 1..9):

| Key         | Description                                             |
| :---------- | :------------------------------------------------------ |
| `n`         | View all windows with `n`th tag.                        |
| `Shift`+`n` | Apply `n`th tag to focused window.                      |
| `Ctrl`+`n`  | Add/remove all windows with `n`th tag to/from the view. |
| `Shift`+`Ctrl`+`n` | Add/remove `n`th tag to/from focused window.     |
| `0`         | View all windows with any tag.                          |
| `Shift`+`0` | Apply all tags to focused window.                       |

The keys `XF86XK_AudioRaiseVolume`, `XF86XK_AudioLowerVolume`,
`XF86XK_AudioMute`, `XF86XK_MonBrightnessUp` and `XF86XK_MonBrightnessDown` work
as expected (and pressing `Shift` will give smaller increments). The key
`XK_Print` will take a screenshot of the selected area and `Shift`+`XK_Print`
will take a screenshot of the whole screen.

A summary of the shortcuts that use letters. First row is `Mod`+`letter`,
second row is `Mod`+`Shift`+`letter` and third row is `Mod`+`Control`+`letter`.

```
┌───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┐
│Q      │W      │E      │R      │T      │Y      │U      │I      │O      │P      │
│close  │       │email  │       │L-tile │       │       │L-mono │session│dmenu  │
│       │       │       │       │L-float│       │       │L-deck │       │       │
│quit   │       │       │       │L-btile│       │       │       │       │       │
└─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┘
  │A      │S      │D      │F      │G      │H      │J      │K      │L      │
  │       │scrot  │       │Firefox│inc gap│Big Mn │Next w.│Prev w.│Sml Mn │
  │       │full sc│       │       │dec gap│       │       │       │       │
  └─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┐
    │Z      │X      │C      │V      │B      │N      │M      │,      │.      │
    │       │Signal │Pass M │       │tgl bar│tmp fil│mount d│Prev sc│Next sc│
    │       │       │Pass M │       │tgl gap│tmp dir│       │Send PS│Send NS│
    └───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
```


[dwm]: <https://dwm.suckless.org> "dwm's homepage"
