#!/usr/bin/env python3
"""
Interactive setup script for Azure OpenAI integration
"""

import os
import sys
import json
import requests
from pathlib import Path
from typing import Optional

class AzureOpenAISetup:
    def __init__(self):
        self.config_file = Path(".azure_openai_config.json")
        self.env_file = Path(".env")
        
    def setup_interactive(self):
        """Interactive setup for Azure OpenAI"""
        print("=" * 60)
        print("Azure OpenAI Setup for LeetCode Automation")
        print("=" * 60)
        
        # Check for existing configuration
        if self.config_file.exists():
            print("\n📁 Found existing configuration.")
            use_existing = input("Use existing configuration? (y/n): ").lower()
            if use_existing == 'y':
                return self.load_config()
        
        print("\n📋 Let's set up your Azure OpenAI connection.")
        print("\nYou'll need:")
        print("1. Azure OpenAI resource endpoint")
        print("2. API key")
        print("3. Deployment name (optional, we can detect it)")
        
        print("\n" + "-" * 40)
        print("To find these in Azure Portal:")
        print("1. Go to https://portal.azure.com")
        print("2. Navigate to your Azure OpenAI resource")
        print("3. Click 'Keys and Endpoint' in the left menu")
        print("-" * 40)
        
        # Get endpoint
        print("\nEndpoint format: https://YOUR-RESOURCE-NAME.openai.azure.com/")
        endpoint = input("Enter your Azure OpenAI endpoint: ").strip()
        
        # Validate endpoint
        if not endpoint.startswith("https://"):
            endpoint = "https://" + endpoint
        if not endpoint.endswith("/"):
            endpoint += "/"
            
        # Get API key
        print("\nAPI Key (will be stored locally, not shown)")
        api_key = input("Enter your API key: ").strip()
        
        # Test connection and detect deployments
        print("\n🔍 Testing connection and detecting deployments...")
        deployments = self.detect_deployments(endpoint, api_key)
        
        deployment_name = None
        if deployments:
            print("\n✅ Connection successful! Found deployments:")
            for i, dep in enumerate(deployments, 1):
                print(f"{i}. {dep['name']} (Model: {dep['model']})")
            
            choice = input("\nSelect deployment number (or press Enter to input manually): ").strip()
            if choice.isdigit() and 1 <= int(choice) <= len(deployments):
                deployment_name = deployments[int(choice) - 1]['name']
            else:
                deployment_name = input("Enter deployment name manually: ").strip()
        else:
            print("\n⚠️  Couldn't auto-detect deployments.")
            deployment_name = input("Enter your deployment name: ").strip()
        
        # Save configuration
        config = {
            "endpoint": endpoint,
            "api_key": api_key,
            "deployment_name": deployment_name,
            "api_version": "2024-02-01"
        }
        
        self.save_config(config)
        
        # Test the configuration
        print("\n🧪 Testing configuration with a simple request...")
        if self.test_connection(config):
            print("✅ Configuration successful!")
            print("\n📝 Configuration saved to:")
            print(f"   - {self.config_file}")
            print(f"   - {self.env_file}")
            print("\n🚀 You're ready to run the automation!")
            return config
        else:
            print("❌ Configuration test failed. Please check your settings.")
            return None
    
    def detect_deployments(self, endpoint: str, api_key: str) -> list:
        """Detect available deployments"""
        headers = {
            "api-key": api_key,
            "Content-Type": "application/json"
        }
        
        url = f"{endpoint}openai/deployments?api-version=2024-02-01"
        
        try:
            response = requests.get(url, headers=headers, timeout=10)
            if response.status_code == 200:
                data = response.json()
                deployments = []
                if 'data' in data:
                    for dep in data['data']:
                        deployments.append({
                            'name': dep.get('id', 'unknown'),
                            'model': dep.get('model', 'unknown'),
                            'status': dep.get('status', 'unknown')
                        })
                return deployments
        except Exception as e:
            print(f"Detection error: {e}")
        
        return []
    
    def test_connection(self, config: dict) -> bool:
        """Test the connection with a simple request"""
        headers = {
            "api-key": config['api_key'],
            "Content-Type": "application/json"
        }
        
        url = f"{config['endpoint']}openai/deployments/{config['deployment_name']}/chat/completions?api-version={config['api_version']}"
        
        payload = {
            "messages": [
                {"role": "system", "content": "You are a helpful assistant."},
                {"role": "user", "content": "Respond with 'Ready!' if you can hear me."}
            ],
            "max_tokens": 10,
            "temperature": 0
        }
        
        try:
            response = requests.post(url, headers=headers, json=payload, timeout=10)
            if response.status_code == 200:
                result = response.json()
                if 'choices' in result and len(result['choices']) > 0:
                    print(f"   Model response: {result['choices'][0]['message']['content']}")
                    return True
            else:
                print(f"   Error: {response.status_code} - {response.text[:200]}")
        except Exception as e:
            print(f"   Connection error: {e}")
        
        return False
    
    def save_config(self, config: dict):
        """Save configuration to files"""
        # Save to JSON
        with open(self.config_file, 'w') as f:
            json.dump(config, f, indent=2)
        
        # Save to .env file
        with open(self.env_file, 'w') as f:
            f.write(f"AZURE_OPENAI_KEY={config['api_key']}\n")
            f.write(f"AZURE_OPENAI_ENDPOINT={config['endpoint']}\n")
            f.write(f"AZURE_OPENAI_DEPLOYMENT={config['deployment_name']}\n")
            f.write(f"AZURE_OPENAI_API_VERSION={config['api_version']}\n")
    
    def load_config(self) -> Optional[dict]:
        """Load existing configuration"""
        try:
            with open(self.config_file, 'r') as f:
                config = json.load(f)
            
            print("\n📋 Loaded configuration:")
            print(f"   Endpoint: {config['endpoint']}")
            print(f"   Deployment: {config['deployment_name']}")
            
            # Test it
            print("\n🧪 Testing connection...")
            if self.test_connection(config):
                print("✅ Connection successful!")
                return config
            else:
                print("❌ Connection failed.")
                retry = input("\nWould you like to reconfigure? (y/n): ").lower()
                if retry == 'y':
                    return self.setup_interactive()
        except Exception as e:
            print(f"Error loading config: {e}")
        
        return None
    
    def show_usage_examples(self):
        """Show how to use the API in code"""
        print("\n" + "=" * 60)
        print("📚 Usage Examples")
        print("=" * 60)
        
        print("\n1. Basic completion:")
        print("""
import os
import requests

api_key = os.environ['AZURE_OPENAI_KEY']
endpoint = os.environ['AZURE_OPENAI_ENDPOINT']
deployment = os.environ['AZURE_OPENAI_DEPLOYMENT']

url = f"{endpoint}openai/deployments/{deployment}/chat/completions?api-version=2024-02-01"
headers = {"api-key": api_key, "Content-Type": "application/json"}

payload = {
    "messages": [
        {"role": "system", "content": "You are a C++ expert."},
        {"role": "user", "content": "Write a function to reverse a string."}
    ],
    "max_tokens": 500,
    "temperature": 0.7
}

response = requests.post(url, headers=headers, json=payload)
print(response.json()['choices'][0]['message']['content'])
""")
        
        print("\n2. For LeetCode automation:")
        print("""
# The automation script will use these environment variables
# to generate solutions automatically
python3 automate_leetcode.py --problems 10 --difficulty easy
""")

def main():
    setup = AzureOpenAISetup()
    config = setup.setup_interactive()
    
    if config:
        setup.show_usage_examples()
        
        print("\n" + "=" * 60)
        print("✅ Setup Complete!")
        print("=" * 60)
        print("\nNext steps:")
        print("1. Run: source .env")
        print("2. Test: python3 check_azure_models.py")
        print("3. Automate: python3 automate_leetcode.py")
    else:
        print("\n❌ Setup incomplete. Please try again.")
        sys.exit(1)

if __name__ == "__main__":
    main()