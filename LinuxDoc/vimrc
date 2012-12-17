" All system-wide defaults are set in $VIMRUNTIME/debian.vim (usually just
" /usr/share/vim/vimcurrent/debian.vim) and sourced by the call to :runtime
" you can find below.  If you wish to change any of those settings, you should
" do it in this file (/etc/vim/vimrc), since debian.vim will be overwritten
" everytime an upgrade of the vim packages is performed.  It is recommended to
" make changes after sourcing debian.vim since it alters the value of the
" 'compatible' option.

" This line should not be removed as it ensures that various options are
" properly set to work with the Vim-related packages available in Debian.
runtime! debian.vim

" Uncomment the next line to make Vim more Vi-compatible
" NOTE: debian.vim sets 'nocompatible'.  Setting 'compatible' changes numerous
" options, so any other options should be set AFTER setting 'compatible'.
"set compatible

" Vim5 and later versions support syntax highlighting. Uncommenting the next
" line enables syntax highlighting by default.
if has("syntax")
  syntax on
endif

"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
"this conmmand is very useful for my laotop X60s, which the screen is 
"so dark...:(

" If using a dark background within the editing area and syntax highlighting
" turn on this option as well
set background=dark

" Uncomment the following to have Vim jump to the last position when
" reopening a file
"if has("autocmd")
"  au BufReadPost * if line("'\"") > 1 && line("'\"") <= line("$") | exe "normal! g'\"" | endif
"endif

" Uncomment the following to have Vim load indentation rules and plugins
" according to the detected filetype.
"if has("autocmd")
"  filetype plugin indent on
"endif

" The following are commented out as they cause vim to behave a lot
" differently from regular Vi. They are highly recommended though.
"set showcmd		" Show (partial) command in status line.
"set showmatch		" Show matching brackets.
"set ignorecase		" Do case insensitive matching
"set smartcase		" Do smart case matching
"set incsearch		" Incremental search
"set autowrite		" Automatically save before commands like :next and :make
"set hidden             " Hide buffers when they are abandoned
"set mouse=a		" Enable mouse usage (all modes)

" Source a global configuration file if available
if filereadable("/etc/vim/vimrc.local")
  source /etc/vim/vimrc.local
endif

"add by tusion at 2012-08-04
"show line number, convenient to debug code
set number
"for C code type auto incdent
set autoindent
set smartindent
set tabstop=4
set shiftwidth=4
"set match mode
set showmatch
"show cluser's line status
set ruler

"for linux source code fo through
"set tags=/home/tusion/linux-source-3.2.0/tags
"set tags=./tags
set tags=/home/tusion/linux-source-3.2.0/tags
set tags+=/home/tusion/program/tags

"for taglsit
let Tlist_Show_One_File=1
let Tlist_Exit_OnlyWindow=1
"vim auto open TagList 
"let Tlist_Auto_Open=1

"switch TagList open or close
map <silent> <F8> :TlistToggle<CR>

let Tlist_Show_Menu=1

"add for cscope
set cscopequickfix=s-,c-,d-,i-,e-
cs add /home/tusion/linux-source-3.2.0/cscope.out /home/tusion/linux-source-3.2.0

