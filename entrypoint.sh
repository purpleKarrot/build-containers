#!/bin/bash

# If we are running docker natively, we want to create a user in the container
# with the same UID and GID as the user on the host machine, so that any files
# created are owned by that user. Without this they are all owned by root.
if [[ -n $BUILDER_UID ]] && [[ -n $BUILDER_GID ]]; then
    groupadd -o -g $BUILDER_GID $BUILDER_GROUP 2> /dev/null
    useradd -o -m -g $BUILDER_GID -u $BUILDER_UID $BUILDER_USER 2> /dev/null
    shopt -s dotglob
    chown -R $BUILDER_UID:$BUILDER_GID /binary

    # Run the command as the specified user/group.
    exec chpst -u :$BUILDER_UID:$BUILDER_GID ctest -S build.cmake "$@"
else
    # Just run the command as root.
    exec ctest -S build.cmake "$@"
fi
