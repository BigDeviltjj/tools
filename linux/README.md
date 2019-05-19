### linux tools:

1. zsh

```
sh -c "$(curl -fsSL https://raw.githubusercontent.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"
```

2. zsh-syntax-highlighting
```
git clone https://github.com/zsh-users/zsh-syntax-highlighting.git
echo "source ${(q-)PWD}/zsh-syntax-highlighting/zsh-syntax-highlighting.zsh" >> ${ZDOTDIR:-$HOME}/.zshrc
```

3. fzf
```
git clone --depth 1 https://github.com/junegunn/fzf.git ~/.fzf
~/.fzf/install
```

3. tmux
```
sudo apt-get install tmux
```

4. vim (ONLY FOR MAC BECAUSE SPACEVIM IN LINUX SUCKS!)
```
brew install ctags-exuberant
curl -sLf https://spacevim.org/install.sh | bash
```

in case of display issues in os X, install nerd-font

```
brew tap caskroom/fonts
brew cask install font-hack-nerd-font
```

then change ```font``` and ```Non-ascii font```  in iterm2 preferences-profilers-text

5. vscode remove server(linux version since remote-server is always centos)
```
cd ~/Downloads
wget https://github.com/cdr/code-server/releases/download/1.939-vsc1.33.1/code-server1.939-vsc1.33.1-linux-x64.tar.gz
tar -zxvf code-server1.939-vsc1.33.1-linux-x64.tar.gz
cd code-server1.939-vsc1.33.1-linux-x64
echo "alias code-server="$(pwd)/code-server"" >> ~/.zshrc
```
