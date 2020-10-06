#!/bin/bash
PS1="\[\033[40m\]\[\033[93m\][\T][\u@\h:\w]> \[$(tput sgr0)\]"
alias l="ls -CF"
alias la="ls -A"
alias ll="ls -alF"
alias ls="ls --color=auto"
