"""
Advanced Python Logging Example
--------------------------------
This script demonstrates a comprehensive logging setup for a web scraper
that demonstrates various logging features and best practices.
"""
import logging
import logging.handlers
import os
import time
import random
from datetime import datetime


class CustomFormatter(logging.Formatter):
    """Custom formatter with colored output for console"""
    
    COLORS = {
        'DEBUG': '\033[94m',      # Blue
        'INFO': '\033[92m',       # Green
        'WARNING': '\033[93m',    # Yellow
        'ERROR': '\033[91m',      # Red
        'CRITICAL': '\033[41m',   # Red background
        'RESET': '\033[0m'        # Reset color
    }
    
    def format(self, record):
        log_message = super().format(record)
        if record.levelname in self.COLORS:
            log_message = f"{self.COLORS[record.levelname]}{log_message}{self.COLORS['RESET']}"
        return log_message


def setup_logging(log_dir="logs"):
    """Set up logging configuration"""
    # Create logs directory if it doesn't exist
    if not os.path.exists(log_dir):
        os.makedirs(log_dir)
    
    # Create logger
    logger = logging.getLogger("web_scraper")
    logger.setLevel(logging.DEBUG)
    
    # Prevent adding handlers multiple times
    if logger.handlers:
        return logger
    
    # Console Handler
    console_handler = logging.StreamHandler()
    console_handler.setLevel(logging.INFO)
    console_format = '%(asctime)s - %(levelname)s - %(message)s'
    console_formatter = CustomFormatter(console_format, datefmt='%H:%M:%S')
    console_handler.setFormatter(console_formatter)
    
    # File Handler for all logs
    file_handler = logging.FileHandler(f"{log_dir}/scraper.log")
    file_handler.setLevel(logging.DEBUG)
    file_format = '%(asctime)s - %(name)s - %(levelname)s - %(funcName)s:%(lineno)d - %(message)s'
    file_formatter = logging.Formatter(file_format, datefmt='%Y-%m-%d %H:%M:%S')
    file_handler.setFormatter(file_formatter)
    
    # Rotating File Handler for errors
    error_handler = logging.handlers.RotatingFileHandler(
        f"{log_dir}/errors.log",
        maxBytes=10485760,  # 10MB
        backupCount=5
    )
    error_handler.setLevel(logging.ERROR)
    error_handler.setFormatter(file_formatter)
    
    # Add handlers to logger
    logger.addHandler(console_handler)
    logger.addHandler(file_handler)
    logger.addHandler(error_handler)
    
    return logger


class WebScraper:
    """Example web scraper class with proper logging"""
    
    def __init__(self, target_url):
        self.logger = logging.getLogger("web_scraper")
        self.url = target_url
        self.session_id = str(random.randint(1000, 9999))
        self.logger.info(f"Initialized WebScraper with session ID: {self.session_id}")
    
    def fetch_page(self, retries=3):
        """Simulates fetching a webpage with occasional failures"""
        self.logger.debug(f"Attempting to fetch URL: {self.url}, retry count: {retries}")
        
        # Simulate HTTP request with random outcome
        chance = random.random()
        
        try:
            # Log request timing with context manager
            with self.log_execution_time("fetch_page"):
                # Simulate network delay
                time.sleep(random.uniform(0.1, 0.5))
                
                if chance < 0.2:  # 20% chance of failure
                    raise ConnectionError("Failed to connect to server")
                elif chance < 0.3:  # 10% chance of timeout
                    raise TimeoutError("Connection timed out")
                
                # Success case
                self.logger.info(f"Successfully fetched {self.url}")
                return f"<html><body>Example content from {self.url}</body></html>"
        
        except (ConnectionError, TimeoutError) as e:
            self.logger.error(f"Error fetching {self.url}: {str(e)}")
            
            if retries > 0:
                self.logger.warning(f"Retrying fetch for {self.url}, {retries} attempts remaining")
                return self.fetch_page(retries - 1)
            else:
                self.logger.critical(f"All retries failed for {self.url}")
                return None
    
    def parse_content(self, html_content):
        """Simulates parsing HTML content"""
        if not html_content:
            self.logger.error("Cannot parse empty content")
            return []
        
        self.logger.debug(f"Parsing HTML content of length {len(html_content)}")
        
        # Simulate parsing with random outcomes
        chance = random.random()
        
        try:
            # Simulate parsing delay
            time.sleep(random.uniform(0.1, 0.3))
            
            if chance < 0.1:  # 10% chance of parsing error
                raise ValueError("Invalid HTML structure")
            
            # Success case
            result = ["Item " + str(i) for i in range(1, 6)]
            self.logger.info(f"Successfully parsed content, found {len(result)} items")
            return result
            
        except ValueError as e:
            self.logger.error(f"Parsing error: {str(e)}")
            return []
    
    def log_execution_time(self, operation_name):
        """Context manager to log execution time of operations"""
        class TimingContext:
            def __init__(self, scraper, operation):
                self.scraper = scraper
                self.operation = operation
                self.start_time = None
            
            def __enter__(self):
                self.start_time = time.time()
                return self
            
            def __exit__(self, exc_type, exc_val, exc_tb):
                execution_time = time.time() - self.start_time
                self.scraper.logger.debug(
                    f"Operation '{self.operation}' completed in {execution_time:.4f} seconds"
                )
        
        return TimingContext(self, operation_name)


def run_demo():
    """Run a demonstration of the scraper with logging"""
    logger = setup_logging()
    logger.info("=" * 50)
    logger.info("Starting web scraper demonstration")
    logger.info("=" * 50)
    
    # Simulate multiple target websites
    websites = [
        "https://example.com/page1",
        "https://example.com/page2",
        "https://example.com/page3",
        "https://invalid-domain.xyz/test"  # Will likely fail
    ]
    
    # Process each website
    results = {}
    for url in websites:
        logger.info(f"Processing website: {url}")
        scraper = WebScraper(url)
        
        # Fetch and process with all logging
        content = scraper.fetch_page()
        items = scraper.parse_content(content)
        
        results[url] = items
    
    # Log the overall results
    successful = sum(1 for items in results.values() if items)
    logger.info(f"Scraping completed. Successfully scraped {successful}/{len(websites)} websites")
    
    if successful < len(websites):
        logger.warning("Some websites could not be scraped. Check the error logs for details.")
    
    return results


if __name__ == "__main__":
    # Run the demo
    results = run_demo()
    
    # Final console output
    print("\nScraping Results:")
    print("----------------")
    for url, items in results.items():
        if items:
            print(f"{url}: Found {len(items)} items")
        else:
            print(f"{url}: Failed to retrieve data")