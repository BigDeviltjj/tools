### linux tools:

1. space vim (FOR MAC) 
```
brew install ctags-exuberant
curl -sLf https://spacevim.org/install.sh | bash
```
in case of display issues in os X, install nerd-font
```
brew tap caskroom/fonts
brew cask install font-hack-nerd-font
```
then change `font` and `Non-ascii font`  in iterm2 preferences-profilers-text 

  markdown, add
  ```
  [[custom_plugins]]
  name = 'iamcco/mathjax-support-for-mkdp'
  merged = 0
  
  [[custom_plugins]]
  name = 'iamcco/markdown-preview.vim'
  merged = 0
  ```
  to `~/.SpaceVim.d/init.toml` then `:MarkDownPreview` in vim
2. vscode remove server(linux version since remote-server is always centos)
```
cd ~/Downloads
wget https://github.com/cdr/code-server/releases/download/1.939-vsc1.33.1/code-server1.939-vsc1.33.1-linux-x64.tar.gz
tar -zxvf code-server1.939-vsc1.33.1-linux-x64.tar.gz
cd code-server1.939-vsc1.33.1-linux-x64
echo "alias code-server="$(pwd)/code-server"" >> ~/.zshrc
```

3. git public key
```
ssh-keygen
cat ~/.ssh/id_rsa.pub
```
copy information to ssh	keys in github

3. useful spacevim hot keys:
```
\ num                 switch to table num
sq                    close opened file
q                     close less important file
:e file               new file
<F3>                  open/close vimfiler
(in vimfiler) sg/sv   open file in split screen 
SPC f f               fzf find file 
SPC s /               global grep
(in vimfiler) i       search for history file
SPC l r               run code
SPC c l               comment/uncomment
:SPUpdate             update plugins
:MarkdownPreview      preview markdown
SPC '                 open shell
```

### tips

---

1. vim: YouCompleteMe have to download the library manually; run `install_vim.sh` to update vim to install spacevim

2. github:
  * show history submit log:`git log --graph --full-history --all --pretty=format:"%h%x09%d%x20%s"`
  * create remote branch and corresponding local branch: `git checkout -b dev origin/dev`
  * make local branch assigned to remote branch: `git branch --set-upstream-to=origin/dev dev`
  * change last commit: `git commit --amend`

