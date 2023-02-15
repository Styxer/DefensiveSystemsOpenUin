from contextlib import contextmanager
from .Constants import DEFAULT_PORT_FILENAME


@contextmanager
def config_file(filename: str = DEFAULT_PORT_FILENAME):
    with open(filename, 'rt') as config:
        config_contents = config.read()
        return int(config_contents)