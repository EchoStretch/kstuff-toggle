#   Copyright (C) 2023 John Törnblom
#
# This file is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; see the file COPYING. If not see
# <http://www.gnu.org/licenses/>.

PS5_HOST ?= ps5
PS5_PORT ?= 9021

ifdef PS5_PAYLOAD_SDK
    include $(PS5_PAYLOAD_SDK)/toolchain/prospero.mk
else
    $(error PS5_PAYLOAD_SDK is undefined)
endif

# Base name for payloads
ELF_BASE := kstuff-toggle

# Option variants to build
OPTIONS := 0 1 2

# Resulting ELF files
ELFS := $(foreach opt,$(OPTIONS),$(ELF_BASE)-$(opt).elf)

CFLAGS := -Wall -Werror

# Default target: build all variants
all: $(ELFS)

# Rule for each option build
$(ELF_BASE)-%.elf: main.c
	@echo "Building payload with OPTION=$*"
	$(CC) $(CFLAGS) -DOPTION=$* -o $@ $^

# Clean all artifacts
clean:
	rm -f $(ELFS) $(ELF_BASE).elf

# Deploy default ELF (option 0) for quick testing
test: $(ELF_BASE)-0.elf
	$(PS5_DEPLOY) -h $(PS5_HOST) -p $(PS5_PORT) $^