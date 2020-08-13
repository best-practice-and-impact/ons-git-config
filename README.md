# ONS Git Configuration

I wanted to share my global Git configuration, to support use of GitHub alongside GitLab at the ONS. It also includes other features that you might find useful in your workflow. Some of these features are described below, with the complete files displayed at the bottom of the page.

Feel free to copy the whole lot, but I'd suggest that you instead choose aspects that might be useful to you and add these to your own configuration.


## Home location

The default location that Git uses to store it's global configuration file (`.gitconfig`) is the `HOME` location. If you use SSH to connect to GitLab/GitHub, ssh also looks for your private key in the `.ssh\` directory here. At the ONS, the default `HOME` location is the networked drive that is mapped to `H:/`, which contains your `Documents\` directory etc. Unfortunately, this drive can disconnect, or become unable to synchronise, when working remotely. When this occurs, Git nor ssh are able to find the required files to function.

**Please only use the following solution if you are having similar issues with `H:/` disconnecting, as it might cause problems with other programs**

To remedy this, I defined a new `HOME` location at a non-networked location on my machine. I've allocated `C:\Users\<my-username>` as `HOME`, though any other location on `C:` or `D:` would work equally as well. To define a new `HOME` location, you can set a user envrionmental variable `HOME` to the path of that location. To do this, find `Edit environment variables for your account` in your machine's settings. Here create a new User variable with the Variable `HOME` and Value corresponding to the new location path.

Once this variable has been defined, you should move any existing `.gitconfig` files and `.ssh\` directories from `H:` to the new location. Be aware that other software may rely on this `HOME` location. In this case, you can either copy any other files to the new path or easily delete the variable and return the filed to `H:`.

If you find that no `.gitconfig` file existed at the old or new `HOME` location, you can create it by setting any custom configuration, for example: `git config --global user.name "John Doe"`


## Conditional includes

With the recent upgrade to Git version (2.27), git configuration now supports [conditional includes](https://git-scm.com/docs/git-config#_conditional_includes). I've used this to select different user name and email parameters, depending on which folder a local repository is located in. I store all repos under `D:\repos\`, where I use one directory for GitLab repos (`ons\`) and another for GitHub (`ext\`). This conditional inclusion allows me to correctly authenticate connection to either GitLab or GitHub, without needing to manually set these parameters for each individual repository.


## Aliases

Aliases can be used to create shortcuts for regularly-used or hard-to-remember Git commads. Most of the examples below shorten regular commands to two letters (e.g. `git status` to `git st`). The last example makes it easier for me to push new local branches to new remote equivalents, as I often forget to use the `--set-upstream` flag when doing this.


## The Setup

My `.gitconfig` looks like this:

[.gitconfig](the_setup/.gitconfig)
```
[includeIf "gitdir:D:/repos/ons/"]
  	path = gitlab.inc

[includeIf "gitdir:D:/repos/ext/"]
  	path = github.inc

[core]
	pager = cat  # This stops me getting trapped in vim, which crashes on Anaconda prompt when using git diff and others

[alias]
	st = status
	co = checkout
	ci = commit
	br = branch
	pushup = "!git push --set-upstream origin $(git symbolic-ref --short HEAD)"  # Shortcut to push new branches to remote equivalent
```

This references two arbitrarily named `.inc` files, which are included for GitLab and GitHub respectively. You'll need to substitute in your own credentials to use parts of these templates. These files should sit next to your `.gitconfig` in the `HOME` directory.

[gitlab.inc](the_setup/gitlab.inc)
```
[user]
	name = <ONS username>
	email = <ONS email>
```

[github.inc](the_setup/github.inc)
```
[user]
	name = <Name>
	email = <Email registered on GitHub>

# The next two sections allow HTTP authentication with GitHub, but using SSH keys is preferable
[http "https://github.com/"]
	extraheader = Authorization: basic <Base64-encoded personal access token (PAT) from GitHub>  # Should ideally reference this key from an environmental variable

[credential "https://github.com/"]
	username = <GitHub username>
```

