# PKGSrc


#
# Copy and paste the lines below to install the Apple Silicon (M1/M2) set.
#
# These packages are suitable for anyone running Big Sur (11.3) or newer on
# Apple Silicon (M1/M2) CPUs, and are updated from pkgsrc trunk every week.
#
# This should only ever be performed once.  Unpacking the bootstrap kit over
# the top of an existing install will probably break things.
#
BOOTSTRAP_TAR="bootstrap-macos11-trunk-arm64-20220928.tar.gz"
BOOTSTRAP_SHA="a6e3a805eba4b3522b6da0a590bda945a34e49dd"

curl -O https://pkgsrc.smartos.org/packages/Darwin/bootstrap/${BOOTSTRAP_TAR}

# Verify the SHA1 checksum.
echo "${BOOTSTRAP_SHA}  ${BOOTSTRAP_TAR}" | shasum -c-

# Verify PGP signature.  This step is optional, and requires gpg.
# curl -O https://pkgsrc.smartos.org/packages/Darwin/bootstrap/${BOOTSTRAP_TAR}.asc
# curl -sS https://pkgsrc.smartos.org/pgp/ED09C4B0.asc | gpg2 --import
# gpg2 --verify ${BOOTSTRAP_TAR}{.asc,}

# Install bootstrap kit to /opt/pkg
sudo tar -zxpf ${BOOTSTRAP_TAR} -C /

# Reload PATH/MANPATH (pkgsrc installs /etc/paths.d/10-pkgsrc for new sessions)
eval $(/usr/libexec/path_helper)
