[user]
	name = <Name>
	email = <Email registered on GitHub>

# The next two sections allow automatic authentication with GitHub
[http "https://github.com/"]
	extraheader = Authorization: basic <Base64 encoded key from GitHub>  # Should ideally reference this from an environmental variable

[credential "https://github.com/"]
	username = <GitHub username>