#!/usr/bin/env bash
#
for file in **/*; do
  # Check if the item is a regular file
  if [[ -f "$file" ]]; then
    # Get the modification time of the file
    modification_time=$(stat -c "%Y" "$file")

    # Convert the modification time to a Git-friendly date format
    git_date=$(date -d @"$modification_time" +"%Y-%m-%d %H:%M:%S")

    # Create a new Git commit for the file with a message containing the modification time
    git add "$file"
    git commit --date="$git_date" -m "Update $file - $modification_time"
  fi
done
