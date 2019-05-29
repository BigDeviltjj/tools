set -e
curl -sLf https://spacevim.org/cn/install.sh | bash
echo "
#=============================================================================
# basic.toml --- basic configuration example for SpaceVim
# Copyright (c) 2016-2017 Wang Shidong & Contributors
# Author: Wang Shidong < wsdjeg at 163.com >
# URL: https://spacevim.org
# License: GPLv3
#=============================================================================

# All SpaceVim option below [option] section
[options]
    # set spacevim theme. by default colorscheme layer is not loaded,
    # if you want to use more colorscheme, please load the colorscheme
    # layer
    colorscheme = "gruvbox"
    colorscheme_bg = "dark"
    # Disable guicolors in basic mode, many terminal do not support 24bit
    # true colors
    enable_guicolors = true
    # Disable statusline separator, if you want to use other value, please
    # install nerd fonts
    statusline_separator = "nil"
    statusline_inactive_separator = "bar"
    buffer_index_type = 4
    windows_index_type = 3
    enable_tabline_filetype_icon = false
    enable_statusline_mode = false
    statusline_unicode_symbols = false
    project_rooter_automatically = 0
    enable_ycm = true
    bootstrap_after = "myspacevim#after"
    # Enable vim compatible mode, avoid changing origin vim key bindings

# Enable autocomplete laye


[[layers]]
name = 'shell'
default_position = 'top'
default_height = 30

[[layers]]
  name = "chinese"

[[layers]]
  name = "lang#c"

[[layers]]
  name = "fzf"

[[layers]]
  name = "lang#python"

[[layers]]
  name = "git"

[[custom_plugins]]
  name = 'iamcco/mathjax-support-for-mkdp' 
  merged = 0

[[custom_plugins]]
  name = 'iamcco/markdown-preview.vim'
  merged = 0
" > ~/.SpaceVim.d/init.toml 

mkdir -p ~/.SpaceVim.d/autoload

echo "
function! myspacevim#after() abort
  let g:ycm_global_ycm_extra_conf = "~/.cache/vimfiles/repos/github.com/Valloric/YouCompleteMe/third_party/ycmd/.ycm_extra_conf.py"
endfunction
" > ~/.SpaceVim.d/autoload/myspacevim.vim
