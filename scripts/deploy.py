import shutil
import subprocess
import os
import sys
from pathlib import Path

import serial
from loguru import logger

import fire

PROJECT_DIR = Path(__file__).parent.parent
CIRCUITPY_DIR = PROJECT_DIR / 'src'


def clear_directory(directory: Path):
    if os.path.exists(directory):
        for item in os.listdir(directory):
            item_path = os.path.join(directory, item)
            if os.path.isdir(item_path):
                shutil.rmtree(item_path)
            else:
                os.unlink(item_path)


class BuildScript(object):
    """Deploying CircuitPython"""

    def deploy(self, destination: str):
        destination = Path(destination)
        logger.info('Remove all files on rp2040')
        clear_directory(destination)
        logger.info('Upload project files')

        for item in os.listdir(CIRCUITPY_DIR):
            src = CIRCUITPY_DIR / item
            dst = destination / item
            logger.info(f'Copy {src} -> {dst}')
            if src.is_dir():
                shutil.copytree(src, dst)
            elif src.is_file():
                shutil.copy(src, dst)
            else:
                raise IOError("Could not deploy")

        logger.info('Deployment done')

    def monitor_tty(self, tty: str):
        logger.info('Monitor tty')
        ser = serial.Serial(tty, 115200)

        try:
            while True:
                line = ser.readline().decode().replace('\n', '')
                logger.info(line)
        except KeyboardInterrupt:
            ser.close()

    def deploy_monitor(self, destination: str, tty: str):
        self.deploy(destination)
        self.monitor_tty(tty)


def main():
    fire.Fire(BuildScript)


if __name__ == "__main__":
    main()
