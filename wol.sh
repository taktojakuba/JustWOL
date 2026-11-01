#!/usr/bin/env bash
set -euo pipefail

declare -A hosts=(
  [pc]=AA:BB:CC:DD:EE:FF
  [nas]=11:22:33:44:55:66
)

name=${1:?usage: wol.sh NAME|MAC [BROADCAST_IP] [PORT]}
mac=${hosts[$name]:-$name}
bcast=${2:-255.255.255.255}
port=${3:-9}

hex=${mac//[:-]/}
[[ $hex =~ ^[0-9A-Fa-f]{12}$ ]] || { echo "invalid MAC: $mac" >&2; exit 1; }

payload=$(printf 'f%.0s' {1..12})$(printf "$hex%.0s" {1..16})
printf "$(sed 's/../\\x&/g' <<<"$payload")" | nc -w1 -u -b "$bcast" "$port"