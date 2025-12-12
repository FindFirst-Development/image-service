FROM alpine:3.23.0 AS base 

FROM base AS build  
# build dependencies.
RUN apk --no-cache add cmake \
  make python3 py3-setuptools py3-pip \
  libc-dev linux-headers gcc g++ 

WORKDIR /prj
COPY ./CMakeLists.txt ./
COPY ./conanfile.txt ./
COPY ./res ./res
COPY ./src ./src

RUN python3 -m venv ./pyenv && \
  . pyenv/bin/activate && \
  pyenv/bin/pip install conan && \
  pyenv/bin/conan profile detect --force && \
  pyenv/bin/conan install . --build=missing && \
  cmake --preset=conan-release && \
  cmake --build --preset=conan-release \
  strip build/Release/Hello_Crow || true 

# Run
FROM base AS runner
RUN apk add --no-cache libstdc++ libgcc
WORKDIR /app
COPY --from=build /prj/build/Release/Hello_Crow ./Hello_Crow
ENTRYPOINT [ "/app/Hello_Crow" ]

