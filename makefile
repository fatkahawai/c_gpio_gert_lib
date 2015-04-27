#
# Makefile
#
# Copyright (C) Pink Pelican NZ Ltd 2015
#
# No rights reserved
# You may treat this program as if it was in the public domain
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
# Keep things simple for novice users
# so do not use any implicit rules!
#

all : libgertboard.so.1

clean :
	rm *.o *.so *.so.1 *.so.1.0 

libgertboard.so.1 : libgertboard.so
	ln -sf libgertboard.so.1.0 libgertboard.so.1 ;\
	export LD_LIBRARY_PATH=.


libgertboard.so : libgertboard.so.1.0
	ln -sf libgertboard.so.1.0 libgertboard.so

libgertboard.so.1.0 : gb_common.o gb_spio.o 
	gcc -shared -Wl,-soname,libgertboard.so.1 -o libgertboard.so.1.0 gb_common.o gb_spio.o

# The next lines generate the various object files

gb_common.o : gb_common.c gb_common.h
	gcc -Wall -fPIC -c gb_common.c 

gb_spio : gb_spio.c gb_spio.h
	gcc -Wall -fPIC -c gb_spio.c

# test.o : test.c halve.h
#	gcc -c test.c
