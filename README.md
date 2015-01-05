cframeworks
===========

Set of frameworks for application development based on [The GNU C Library (glibc)](https://www.gnu.org/software/libc/)
and [GNOME GLib](https://developer.gnome.org/glib/stable/index.html).


###### Notes

Test with:
```bash
$ LANG=sr_RS@latin ./glibframework
```

Do memory profiling with:
```bash
$ LANG=sr_RS@latin profilemyapp ./glibframework
```

Make sure that `/etc/profile.d/lang.*` configuration files are set in a proper
way, i.e.:
```bash
/etc/profile.d/lang.sh
export LANG=en_US.UTF-8
#export LANGUAGE=en_US.UTF-8
#export LINGUAS=en_US.UTF-8
#export LC_ALL=en_US.UTF-8

/etc/profile.d/lang.csh
setenv LANG en_US.UTF-8
#setenv LANGUAGE en_US.UTF-8
#setenv LINGUAS en_US.UTF-8
#setenv LC_ALL en_US.UTF-8
```
