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
	android-ndk \
	android-standalone \
	arm-linux-gnueabihf \
	clang-11 \
	clang-11-clazy \
	gcc-10 \
	mingw-w64-i686 \
	mingw-w64-x86-64 \
	wine32-gcc \
	wine64-gcc

all: $(IMAGES)

test: $(addprefix test-,$(IMAGES))

base:
	$(DOCKER) build -t $(ORG)/base:$(TAG) _base

clang-11-clazy: clang-11

$(IMAGES): base
	$(DOCKER) build -t $(ORG)/$@:$(TAG) $@

test-%: %
	mkdir -p _binary/$<
	mkdir -p _prefix/$<
	docker run --rm \
	  --volume $(shell pwd)/_test:/source:ro \
	  --volume $(shell pwd)/_binary/$<:/binary \
	  --volume $(shell pwd)/_prefix/$<:/prefix \
	  $(ORG)/$< \
	  -DBUILD_CONFIGURATIONS="Release;Debug" \
	  -DBUILD_STEPS="clean;configure;build;test" \
	  --extra-verbose

display_images:
	for image in $(IMAGES); do echo $$image; done

push:
	docker push $(ORG)/base:$(TAG)
	for image in $(IMAGES); do docker push $(ORG)/$$image:$(TAG); done

pull:
	docker pull $(ORG)/base:$(TAG)
	for image in $(IMAGES); do docker pull $(ORG)/$$image:$(TAG); done

.PHONY: base $(IMAGES)
