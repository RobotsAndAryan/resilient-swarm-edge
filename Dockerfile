FROM ros:iron-ros-base
SHELL ["/bin/bash", "-c"]
WORKDIR /ros2_ws
COPY ./src /ros2_ws/src

RUN apt-get update && rosdep install -y \
    --from-paths src \
    --ignore-src \
    --rosdistro iron \
    && rm -rf /var/lib/apt/lists/*

RUN source /opt/ros/iron/setup.bash && \
    colcon build --symlink-install

COPY ./entrypoint.sh /
ENTRYPOINT ["/entrypoint.sh"]
CMD ["ros2", "run", "swarm_core_bridge", "core_bridge_node"]
