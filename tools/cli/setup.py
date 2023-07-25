from setuptools import setup, find_packages
import os

setup(
    name="anckor CLI",
    version="0.0.1",
    description="A swiss-army knife tool for the Anckor project",
    license="SPL-3",

    packages=find_packages(),
    entry_points={
        'console_scripts': (
            'anckor = src.top:main',
        )
    },
)