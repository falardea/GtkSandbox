# GtkSandbox
#### Copyright (c)?

<p>
    This is a home project to explore some GTK3, maybe evolving into a GTK4 project.  It is intended to evolve considerably as a bit of a sandbox.  The git history may capture more of this evolution than this README, we'll see.
</p>
<p>
    First thing I want to document, that may help me (someone else) someday... how to get a GTK window to show up on a Windows box.  After trying a number of different X servers that were recommended on SO, I found <a href="https://mobaxterm.mobatek.net/">MobaXterm</a>, which actually seemed to present a display server to the windows.  Their home edition works fine, and their license isn't that much
</p>
<p>
    You also want to pre-configure:

    setting->X11->X11 remote access [full]
</p>
<p>
    <small>
        TODO: buy license
    </small>
</p>
<p>
    Next is to let the WSL2 (or CLion in my case) environment know where the display is:
</p>

``
export DISPLAY="`grep nameserver /etc/resolv.conf | sed 's/nameserver //'`:0"
``

<p>
    <small>
        Thanks to <a href="https://stackoverflow.com/questions/61860208/running-graphical-linux-desktop-applications-from-wsl-2-error-e233-cannot-op">SO</a>, as usual.
    </small>
</p>
<p>
    Next, or first?, we need to install cmake and gtk into WSL2.  I found this <a href="https://www.peteronion.org.uk/GtkExamples/GladeTutorials.html">tutorial</a> was the best starting point to make sure things are running correctly, since you can just pop up a window and see that our display server is working or not.
</p>
<p>Thanks to Peter Onion</p>


