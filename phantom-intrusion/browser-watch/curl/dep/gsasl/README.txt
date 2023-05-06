# GNU SASL README -- Important introductory notes.

GNU SASL is an implementation of the Simple Authentication and
Security Layer (SASL) framework and a few common SASL mechanisms.
SASL is used by network servers (e.g., IMAP, SMTP, XMPP) to request
authentication from clients, and in clients to authenticate against
servers.

GNU SASL consists of a C library (libgsasl), a command-line
application (gsasl), and a manual.  The library supports the
ANONYMOUS, CRAM-MD5, DIGEST-MD5, EXTERNAL, GS2-KRB5, GSSAPI, LOGIN,
NTLM, OPENID20, PLAIN, SCRAM-SHA-1, SCRAM-SHA-1-PLUS, SCRAM-SHA-256,
SCRAM-SHA-256-PLUS, SAML20, and SECURID mechanisms.

The library is widely portable to any C89 platform.  The command-line
application requires POSIX or Windows for network communication.

The [GNU SASL web page](https://www.gnu.org/software/gsasl/) provides
current information about the project.

# License

The GNU SASL Library (lib/) is licensed under the GNU Lesser General
Public License (LGPL) version 2.1 (or later).  See the file
COPYING.LIB.  The GNU project typically uses the GNU General Public
License (GPL) for libraries, and not the LGPL, but for this project we
decided that we would get more help from the community if we used the
LGPLv2.1+, as other free SASL implementations exists.  See also
<https://www.gnu.org/licenses/why-not-lgpl.html>.

The command-line application and test suite (src/ and tests/) are
licensed under the GNU General Public License license version 3.0 (or
later).  See the file COPYING.

The documentation (doc/) is licensed under the GNU Free Documentation
License version 1.3 (or later).  See the file doc/fdl-1.3.texi.

For any copyright year range specified as YYYY-ZZZZ in this package
note that the range specifies every single year in that closed
interval.

# Support

If you need help to use GNU SASL, or wish to help others, you are
invited to join our mailing list help-gsasl@gnu.org, see
<https://lists.gnu.org/mailman/listinfo/help-gsasl>.

Things left to do below.  If you like to start working on anything,
please let me know so work duplication can be avoided.

* Support channel bindings in GS2.
* Authentication infrastructure implementing the callbacks for PAM,
  Kerberos, SQL, etc.  Separate project?  GNU Mailutils has some
  starting points for this, but the API is inflexible.
* Provide standard callbacks for tty, GTK, gpg-agent etc.  Probably
  should be a separate library.
* Port applications to use libgsasl
* Bug: If gsasl_decode is handed a string longer than one SASL token,
  the remaining data will be discarded.  This means if the sender
  packed two SASL tokens in one network packet, only the first will be
  seen.  The en/de-code functions should buffer the left over data
  until the next invocation.  Later: it isn't clear that people
  actually need the security layer feature, and it seems better to
  punt to TLS.
* Security layer improvements (e.g., DES and AES in DIGEST-MD5).
* Cleanup code, possibly by using some string abstraction library.
* Privacy separation (authenticate in one process, pass state to another).
* Improve documentation
* Port to Cyclone? CCured?

----------------------------------------------------------------------
Copyright (C) 2002-2022 Simon Josefsson
Copying and distribution of this file, with or without modification,
are permitted in any medium without royalty provided the copyright
notice and this notice are preserved.
