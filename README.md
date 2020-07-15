# ONS Git Configuration

I wanted to share my global Git configuration, to support use of GitHub alongside GitLab at the ONS. It also includes other features that you might find useful in your workflow. Some of these features are described below, with the complete files displayed at the bottom of the page. 


## Location location location

The default location that Git uses to store it's global configuration file (`.gitconfig`) is the "Home" drive. If you use SSH to connect to GitLab/GitHub, ssh also looks for your private key in the `.ssh\` directory here. At the ONS, "Home" is the networked drive that is mapped to `H:/`, which contains your `Documents\` directory etc. Unfortunately, this drive regularly disconnects, or is unable to syncronise, when working remotely. When this occurs, Git nor ssh are able to find the required files to function.

To remedy this, I defined a new "Home" location at a non-networked location on my machine. I've allocated `C:\Users\<my-ons-username>` as "Home", though any other location on `C:` or `D:` would work equally as well. To define a new "Home" location, you can set a user envrionmental variable `HOME` to the path of that location. To do this, find `Edit environmental variables for your account` in your machine's settings. Here create a new User variable with the Variable `HOME` and Value corresponding to the new location path.

Once this variable has been defined, you should move any existing `.gitconfig` files or `.ssh\` directories from `H:` to the new location. Be aware that other software may rely on this "Home" location. In this case, you can either copy any other files to the new path or easily delete the variable and return the filed to `H:`.


## Conditional includes

With the recent upgrade to the latest Git version (2.27), the configuration now supports [conditional includes](https://git-scm.com/docs/git-config#_conditional_includes). I've used this to select different user name and email parameters, depending on which folder a local repository is located in. I store all repos under `D:\repos\`, where I use one directory for GitLab repos (`ons\`) and another for GitHub (`ext\`). This conditional inclusion allows me to correctly authenticate connection to either GitLab or GitHub, without needing to manually set these parameters for each individual repository.


## Aliases

Aliases can be used to create shortcuts for regularly-used or hard-to-remember Git commads. Most of the examples below shorten regular commands to two letters (e.g. `git status` to `git st`). The last example makes it easier for me to push new local branches to new remote equivalents, as I often forget to use the `--set-upstream` flag when doing this.


## The Setup

My `.gitconfig` looks like this:

[.gitconfig](the_setup/.gitconfig)

This references two arbitrarily named `.inc` files, which are included for GitLab and GitHub respectively. You'll need to substitute in your own credentials to use these template.

`gitlab.inc`:
[gitlab.inc](the_setup/gitlab.inc)

`github.inc`:
[github.inc](the_setup/github.inc)

