
GENERATED_SOURCES = Parser.cpp Scanner.cpp
SOURCES = $(GENERATED_SOURCES) $(filter-out $(GENERATED_SOURCES), $(wildcard *.cpp) )
TEST_FILES = $(wildcard ./*.java)
TARGETNAME = compiler
CC = g++
CPPFLAGS = -Wall -std=c++0x -Wno-reorder
LDFLAGS =
FLEX = flex
FLEXFLAGS =
BISON = bison
BISONFLAGS = -v
OBJDIR = objs
$(shell mkdir -p $(OBJDIR) >/dev/null)

OBJECTS = $(addprefix $(OBJDIR)/, $(SOURCES:.cpp=.o) )

Debug: $(TARGETNAME) Tests

$(TARGETNAME): $(GENERATED_SOURCES) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGETNAME)

cleanDebug: clean

clean:
	rm -f $(OBJECTS)
	rm -f $(GENERATED_SOURCES)
#	rm -f $(GENERATED_SOURCES:.cpp=.h)
	rm -f $(TARGETNAME)

Tests: $(TEST_FILES) $(TARGETNAME)
	for testfile in $(TEST_FILES); do ./$(TARGETNAME) $$testfile 2>&1 ; done

.PHONY: Tests Debug

# unit make tasks
$(OBJDIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

Scanner.cpp: lexer.flex
	$(FLEX) $(FLEXFLAGS) $<

Parser.cpp: parser.bison
	$(BISON) $(BISONFLAGS) $<


# dependencies tracker
DEPDIR := .dependencies
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.temp.d

$(OBJDIR)/%.o : %.cpp
$(OBJDIR)/%.o : %.cpp $(DEPDIR)/%.d
	$(CC) $(DEPFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c $< -o $@
	mv -f $(DEPDIR)/$*.temp.d $(DEPDIR)/$*.d

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

-include $(patsubst %,$(DEPDIR)/%.d,$(basename $(SOURCES)))
