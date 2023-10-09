   FROM binder/base-notebook

   USER root

   RUN apt-get update && \
       apt-get install -y build-essential

   USER jovyan
