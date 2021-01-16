#!/bin/bash
PS1="\[\033[38;2;255;255;0m\]\[\033[93m\][\T][\u@\h:\w]> \[$(tput sgr0)\]"
alias l="ls -CF"
alias la="ls -A"
alias ll="ls -alF"
alias ls="ls --color=auto"
alias wine='PULSE_LATENCY_MSEC=60 wine'
