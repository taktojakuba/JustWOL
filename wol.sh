#!/usr/bin/env bash
set -euo pipefail

mac=${1:?usage: wol.sh MAC [BROADCAST_IP] [PORT]}
bcast=${2:-255.255.255.255}
port=${3:-9}

hex=${mac//[:-]/}
[[ $hex =~ ^[0-9A-Fa-f]{12}$ ]] || { echo "invalid MAC: $mac" >&2; exit 1; }

payload=$(printf 'f%.0s' {1..12})$(printf "$hex%.0s" {1..16})
printf "$(sed 's/../\\x&/g' <<<"$payload")" > "/dev/udp/$bcast/$port"