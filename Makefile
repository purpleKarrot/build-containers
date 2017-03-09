# Name of the docker executable
DOCKER = docker

# Docker organization
ORG = purplekarrot

TAG = $(shell git rev-parse --abbrev-ref HEAD)
ifeq ($(TAG), master)
TAG = latest
endif

# List of builder images
IMAGES = \
	android-ndk-r13b \
	arm-linux-gnueabihf \
	clang-3.8 \
	clang-3.8-clazy \
	clang-3.9 \
	clang-3.9-clazy \
	clang-4.0 \
	clang-5.0 \
	gcc-5 \
	gcc-6 \
	mingw-w64-i686 \
	mingw-w64-x86-64 \
	msvc-9.0 \
	wine32-gcc \
	wine64-gcc

all: $(IMAGES)

base:
	$(DOCKER) build -t $(ORG)/base:$(TAG) base

clang-3.8-clazy: clang-3.8
clang-3.9-clazy: clang-3.9

$(IMAGES): base
	$(DOCKER) build -t $(ORG)/$@:$(TAG) $@

display_images:
	for image in $(IMAGES); do echo $$image; done

push:
	docker push $(ORG)/base:$(TAG)
	for image in $(IMAGES); do docker push $(ORG)/$$image:$(TAG); done

pull:
	docker pull $(ORG)/base:$(TAG)
	for image in $(IMAGES); do docker pull $(ORG)/$$image:$(TAG); done

prefix=/usr/local

install:
	install -m 0755 cibuild $(prefix)/bin

.PHONY: base $(IMAGES)
