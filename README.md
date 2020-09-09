# Git Configuration

I wanted to share some tips on Git configuration, to support use of GitHub alongside GitLab at the ONS.
This page also includes other features that you might find useful in your workflow.

For general usage of Git, you can refer to the online [Pro Git](https://git-scm.com/book/en/v2) book.

## Issues

These are issues which this document might help you resolve:

1. My `.gitconfig` or SSH keys are not found, due to the remote `H:/` drive not correctly syncing
2. When I commit to a GitHub repository, commits are attributed to my ONS username/email but not my personal GitHub account
3. I want to use different Git configuration settings for my GitHub and ONS GitLab repositories, but don't want to set these individually for each repository
4. I'm tired of typing long or complex Git commands
5. My console keeps getting stuck when git writes a long output or I forget to write a commit message

Outstanding issues:

* SHH authentication doesn't currently work for repositories outside of the ONS network (GitHub), because `ssh` isn't configured to use the Windows certificate library for SSL.


## 1. Home location

The default location that Git uses to store it's global configuration file (`.gitconfig`) is the `HOME` location. If you use SSH to connect to GitLab/GitHub, ssh also looks for your private key in the `.ssh\` directory here. At the ONS, the default `HOME` location is the networked drive that is mapped to `H:/`, which contains your `Documents\` directory etc. Unfortunately, this drive can disconnect, or become unable to synchronise, when working remotely. When this occurs, Git nor ssh are able to find the required files to function.

**Please only use the following solution if you are having similar issues with `H:/` disconnecting, as this fix might cause problems with other programs that store files here**

To remedy this, I defined a new `HOME` location at a non-networked location on my machine. I've allocated `C:\Users\<my-username>` as `HOME`, though any other location on `C:` or `D:` would work equally as well. To define a new `HOME` location, you can set a user envrionmental variable `HOME` to the path of that location. To do this, find `Edit environment variables for your account` (not system variables) in your machine's settings. Here create a new User variable with the Variable `HOME` and Value corresponding to the new location path.

Once this variable has been defined, you should move any existing `.gitconfig` files and `.ssh\` directories from `H:` to the new location. Be aware that other software may rely on this `HOME` location. If you find this is case, you can either copy the required files to the new path or easily delete the environment variable and return the Git files to `H:` to undo the fix.

If you find that no `.gitconfig` file existed at the old or new `HOME` location, you don't need to move it. If you'd like to provide additional configuration for other steps in this guide, you can create an empty text file at the new `HOME` location named `.gitconfig.`. Note the additional `.` at the end, to indicate that there is no file extension.


## 2. Attribution

GitHub uses the commit-author's email address to attribute commits to a GitHub account. If you find that your commits are not being attributed to your account because it was created with a personal email address, you can [add your ONS email address to the account](https://github.com/settings/emails). Your username on your ONS machine will still be set to your GitLab user.name, but any commits authored by either email address will still be attributed to your account.

## 3. Conditional includes

If you don't want to add your ONS email to your GitHub account, or would like to use a different configuration for GitLab and GitHub repositories, you can use the following setup.

With the recent upgrade to Git version (2.27), git configuration now supports [conditional includes](https://git-scm.com/docs/git-config#_conditional_includes). I've used this, to select different user name and email parameters, depending on which folder a local repository is located in. I store all repos under `D:\repos\`, where I use one directory for GitLab repos (`ons\`) and another for GitHub (`ext\`). This conditional inclusion allows me to correctly authenticate connection to either GitLab or GitHub, without needing to manually set these parameters for each individual repository.

For example, to provide different user name and email settings you might use the following configuration:

[.gitconfig](the_setup/.gitconfig)
```
[includeIf "gitdir:D:/repos/ons/"]
  	path = gitlab.inc

[includeIf "gitdir:D:/repos/ext/"]
  	path = github.inc
```

This conditionally includes configuration options depending on which folder you are working from. I keep all repositories under `D:/repos`, with all GitLab repos stored under the `ons/` directory and all GitHub repos under `ext/`. You can use any names here, but make sure that the `.gitconfig` reflects these names.

The `.gitconfig` above references two arbitrarily named `.inc` files, which are conditionally included for GitLab and GitHub respectively. You'll need to substitute in your own credentials to use parts of these templates. These files should sit next to your `.gitconfig` in the current `HOME` directory.

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

# The next two sections allow HTTP authentication with GitHub
[http "https://github.com/"]
	extraheader = Authorization: basic <Base64-encoded personal access token (PAT) from GitHub>  # Should ideally reference this key from an environmental variable

[credential "https://github.com/"]
	username = <GitHub username>
```

## 4. Aliases

Aliases can be used to create shortcuts for common or hard-to-remember Git commads. Most of the examples below shorten regular commands to two letters (e.g. `git status` to `git st`). While the last example makes it easier for me to push new local branches to new remote equivalents, as I often forget to use the `--set-upstream` flag when doing this.

To create aliases, use 

```
[alias]
	st = status
	co = checkout
	ci = commit
	br = branch
	pushup = "!git push --set-upstream origin $(git symbolic-ref --short HEAD)"  # Shortcut to push new branches to remote equivalent
```

This might look like quite a minimal time gain, but when you commit often it can make the workflow feel faster.

## 5. Getting unstuck

When Git produces a long output (e.g. from `git diff` or `git log`), it uses the default pager `less` to allow you to scroll through the output. You can scroll up and down using arrows keys or use space to move down one page. To exit this scollable output, press `q`. If you don't like using this scrollable pager, you can configure git to print all of the content to the console using `git config --global pager.cat`.

If you make a commit using `git commit` (or other command that requires a message), but don't provide a message with the `-m` flag, Git will open the default text editor `vim`. You can find a list of useful Vim commands [here](https://gist.github.com/CoolOppo/8832717), though most often you will want to write your commit message then press `Esc`, type `:x` and hit `Enter` to save the message and exit.

`Vim` isn't the easiest editor to get to grips with, so you might want set an alternative default editor. For example, to set notepad as your editor, you can use: `git config --global core.editor notepad`. Other editors might require you to provide the path to their excecutable (`.exe`).

