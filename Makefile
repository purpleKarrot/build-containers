# Name of the docker executable
DOCKER = docker

# Docker organization
ORG = purplekarrot

# List of builder images
IMAGES = \
	android-ndk-r13b \
	arm-linux-gnueabihf \
	clang-3.8 \
	clang-3.8-clazy \
	clang-3.9 \
	clang-3.9-clazy \
	gcc-5 \
	gcc-6 \
	mingw-w64-i686 \
	mingw-w64-x86-64 \
	msvc-9.0 \
	wine32-gcc \
	wine64-gcc

all: $(IMAGES)

base:
	$(DOCKER) build -t $(ORG)/base .

clang-3.8-clazy: clang-3.8
clang-3.9-clazy: clang-3.9

$(IMAGES): base
	$(DOCKER) build -t $(ORG)/$@ $@

display_images:
	for image in $(IMAGES); do echo $$image; done

push:
	for image in $(IMAGES); do docker push $(ORG)/$$image; done

prefix=/usr/local

install:
	install -m 0755 bin/cibuild $(prefix)/bin

.PHONY: base $(IMAGES)
