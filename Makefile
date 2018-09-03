CC=g++
INCLDIR = $(SRCDIR)/include
ODIR = obj
BINDIR = bin
SRCDIR = src
INSTALL_DIR = /usr/bin
SYSTEMD_INSTALL_DIR = /lib/systemd/system

EXECUTABLE_NAME = diperan

CFLAGS = -O2 -fPIC -std=c++11 -Wall
CINCLUDES = -I $(INCLDIR) \
	        -I $(SRCDIR)
LIBS= -lpthread -lpapi -lzyre -lczmq -lzmq
DEBUG_FLAGS = -g3 -ggdb -rdynamic

DEPS =
OBJ = $(ODIR)/init.o \
      $(ODIR)/sender.o \
      $(ODIR)/listener.o \
      $(ODIR)/in_processor.o \
      $(ODIR)/in_processor_helpers_m.o \
      $(ODIR)/in_processor_helpers_n.o \
      $(ODIR)/peer_discovery.o \
      $(ODIR)/peer_pruning.o \
      $(ODIR)/peer_discovery_helpers.o \
      $(ODIR)/packet_creation.o \
      $(ODIR)/system_info.o \
      $(ODIR)/caches_info.o \
      $(ODIR)/find_supported_events.o \
      $(ODIR)/counters.o \
      $(ODIR)/matrix_multiplication.o \
      $(ODIR)/crc32.o \
      $(ODIR)/sha2.o \
      $(ODIR)/run_benchmark.o \
      $(ODIR)/command_pkt_creation.o \
      $(ODIR)/master.o \
	  $(ODIR)/main.o

.PHONY: all clean install uninstall

$(ODIR)/%.o: $(SRCDIR)/master/%.cpp $(DEPS)
	@mkdir -p $(ODIR)
	@echo Compiling $< to $@
	@$(CC) -c -o $@ $< $(CFLAGS) $(CINCLUDES)

$(ODIR)/%.o: $(SRCDIR)/master/helpers/%.cpp $(DEPS)
	@mkdir -p $(ODIR)
	@echo Compiling $< to $@
	@$(CC) -c -o $@ $< $(CFLAGS) $(CINCLUDES)

$(ODIR)/%.o: $(SRCDIR)/hardware/%.cpp $(DEPS)
	@mkdir -p $(ODIR)
	@echo Compiling $< to $@
	@$(CC) -c -o $@ $< $(CFLAGS) $(CINCLUDES)

$(ODIR)/%.o: $(SRCDIR)/benchmarking/%.cpp $(DEPS)
	@mkdir -p $(ODIR)
	@echo Compiling $< to $@
	@$(CC) -c -o $@ $< $(CFLAGS) $(CINCLUDES)

$(ODIR)/%.o: $(SRCDIR)/benchmarking/benchmarks/%.cpp $(DEPS)
	@mkdir -p $(ODIR)
	@echo Compiling $< to $@
	@$(CC) -c -o $@ $< $(CFLAGS) $(CINCLUDES)

$(ODIR)/%.o: $(SRCDIR)/benchmarking/algorithms/%.cpp $(DEPS)
	@mkdir -p $(ODIR)
	@echo Compiling $< to $@
	@$(CC) -c -o $@ $< $(CFLAGS) $(CINCLUDES)

$(ODIR)/%.o: $(SRCDIR)/hardware/system_info/%.cpp $(DEPS)
	@mkdir -p $(ODIR)
	@echo Compiling $< to $@
	@$(CC) -c -o $@ $< $(CFLAGS) $(CINCLUDES)

$(ODIR)/%.o: $(SRCDIR)/hardware/system_info/caches/%.cpp $(DEPS)
	@mkdir -p $(ODIR)
	@echo Compiling $< to $@
	@$(CC) -c -o $@ $< $(CFLAGS) $(CINCLUDES)

$(ODIR)/%.o: $(SRCDIR)/network/%.cpp $(DEPS)
	@mkdir -p $(ODIR)
	@echo Compiling $< to $@
	@$(CC) -c -o $@ $< $(CFLAGS) $(CINCLUDES)

$(ODIR)/%.o: $(SRCDIR)/network/incoming/%.cpp $(DEPS)
	@mkdir -p $(ODIR)
	@echo Compiling $< to $@
	@$(CC) -c -o $@ $< $(CFLAGS) $(CINCLUDES)

$(ODIR)/%.o: $(SRCDIR)/network/outgoing/%.cpp $(DEPS)
	@mkdir -p $(ODIR)
	@echo Compiling $< to $@
	@$(CC) -c -o $@ $< $(CFLAGS) $(CINCLUDES)

$(ODIR)/%.o: $(SRCDIR)/processing/%.cpp $(DEPS)
	@mkdir -p $(ODIR)
	@echo Compiling $< to $@
	@$(CC) -c -o $@ $< $(CFLAGS) $(CINCLUDES)

$(ODIR)/%.o: $(SRCDIR)/processing/incoming/%.cpp $(DEPS)
	@mkdir -p $(ODIR)
	@echo Compiling $< to $@
	@$(CC) -c -o $@ $< $(CFLAGS) $(CINCLUDES)

$(ODIR)/%.o: $(SRCDIR)/processing/incoming/master/%.cpp $(DEPS)
	@mkdir -p $(ODIR)
	@echo Compiling $< to $@
	@$(CC) -c -o $@ $< $(CFLAGS) $(CINCLUDES)

$(ODIR)/%.o: $(SRCDIR)/processing/incoming/node/%.cpp $(DEPS)
	@mkdir -p $(ODIR)
	@echo Compiling $< to $@
	@$(CC) -c -o $@ $< $(CFLAGS) $(CINCLUDES)

$(ODIR)/%.o: $(SRCDIR)/processing/outgoing/%.cpp $(DEPS)
	@mkdir -p $(ODIR)
	@echo Compiling $< to $@
	@$(CC) -c -o $@ $< $(CFLAGS) $(CINCLUDES)

$(ODIR)/%.o: $(SRCDIR)/processing/outgoing/master/%.cpp $(DEPS)
	@mkdir -p $(ODIR)
	@echo Compiling $< to $@
	@$(CC) -c -o $@ $< $(CFLAGS) $(CINCLUDES)

$(ODIR)/%.o: $(SRCDIR)/processing/outgoing/node/%.cpp $(DEPS)
	@mkdir -p $(ODIR)
	@echo Compiling $< to $@
	@$(CC) -c -o $@ $< $(CFLAGS) $(CINCLUDES)

$(ODIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	@mkdir -p $(ODIR)
	@echo Compiling $< to $@
	@$(CC) -c -o $@ $< $(CFLAGS) $(CINCLUDES)

all: $(EXECUTABLE_NAME)

$(EXECUTABLE_NAME):  $(OBJ)
	@echo Creating the $@ client daemon
	@mkdir -p $(BINDIR)
	@$(CC) -o $(BINDIR)/$@ $^ $(CFLAGS) $(LIBS)
	@echo $@ daemon is ready in $(BINDIR)
	@echo

clean:
	@echo Deleting the daemon binary and object files
	@-rm -f $(BINDIR)/$(EXECUTABLE_NAME)
	@-rm -f $(ODIR)/*.o
	@echo Cleaning Done
	@echo

install:
	@echo Stopping $(EXECUTABLE_NAME) service
	@-systemctl stop $(EXECUTABLE_NAME).service

	@echo Installing the daemon to $(INSTALL_DIR)/$(EXECUTABLE_NAME)
	@cp $(BINDIR)/$(EXECUTABLE_NAME) $(INSTALL_DIR)/$(EXECUTABLE_NAME)

	@echo Changing executable permissions
	@chmod 764 $(INSTALL_DIR)/$(EXECUTABLE_NAME)

	@echo Copying systemd service file to $(SYSTEMD_INSTALL_DIR)
	@cp ./systemd_service/$(EXECUTABLE_NAME).service $(SYSTEMD_INSTALL_DIR)/$(EXECUTABLE_NAME).service

	@echo Changing systemd service file permissions
	@chmod 664 $(SYSTEMD_INSTALL_DIR)/$(EXECUTABLE_NAME).service

	@echo Reloading systemd daemon
	@systemctl daemon-reload

	@echo Enabling $(EXECUTABLE_NAME) service
	@systemctl enable $(EXECUTABLE_NAME).service

	@echo Starting $(EXECUTABLE_NAME) service
	@systemctl start $(EXECUTABLE_NAME).service

	@echo Installing Done
	@echo

uninstall:
	@echo Stopping $(EXECUTABLE_NAME) service
	@-systemctl stop $(EXECUTABLE_NAME).service

	@echo Disabling $(EXECUTABLE_NAME) service
	@-systemctl disable $(EXECUTABLE_NAME).service

	@echo Uninstalling $(EXECUTABLE_NAME)
	@-rm $(INSTALL_DIR)/$(EXECUTABLE_NAME)

	@echo Removing service file
	@-rm $(SYSTEMD_INSTALL_DIR)/$(EXECUTABLE_NAME).service

	@echo Reloading systemd daemon
	@-systemctl daemon-reload
	
	@echo Uninstalling Done
	@echo
