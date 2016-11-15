# Name of the docker executable
DOCKER = docker

# Docker organization
ORG = purplekarrot

# List of builder images
IMAGES = \
	arm-linux-gnueabihf \
	clang-3.8 \
	clang-3.9 \
	gcc-5 \
	gcc-6

all: $(IMAGES)

base:
	$(DOCKER) build -t $(ORG)/base .

$(IMAGES): base
	$(DOCKER) build -t $(ORG)/$@ $@

display_images:
	for image in $(IMAGES); do echo $$image; done

prefix=/usr/local

install:
	install -m 0755 bin/cibuild $(prefix)/bin

.PHONY: base $(IMAGES)
