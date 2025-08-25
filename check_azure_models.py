#!/usr/bin/env python3
"""
Check available Azure OpenAI models and deployments
"""

import os
import requests
import json
from typing import Dict, List

def check_azure_openai_models():
    """Check available models in Azure OpenAI"""
    
    # Try to get credentials from environment variables
    api_key = os.environ.get('AZURE_OPENAI_KEY', '')
    endpoint = os.environ.get('AZURE_OPENAI_ENDPOINT', '')
    
    if not api_key or not endpoint:
        print("Azure OpenAI credentials not found in environment variables.")
        print("\nPlease set the following environment variables:")
        print("  export AZURE_OPENAI_KEY='your-api-key'")
        print("  export AZURE_OPENAI_ENDPOINT='your-endpoint'")
        print("\nOr you can create a .env file with these values.")
        print("\nYou can find these in your Azure Portal:")
        print("  1. Go to your Azure OpenAI resource")
        print("  2. Click on 'Keys and Endpoint' in the left menu")
        print("  3. Copy Key 1 or Key 2 for AZURE_OPENAI_KEY")
        print("  4. Copy the Endpoint for AZURE_OPENAI_ENDPOINT")
        return
    
    print(f"Endpoint: {endpoint}")
    print("=" * 50)
    
    # Azure OpenAI API version
    api_version = "2024-02-01"
    
    headers = {
        "api-key": api_key,
        "Content-Type": "application/json"
    }
    
    # Try to list deployments
    deployments_url = f"{endpoint}/openai/deployments?api-version={api_version}"
    
    try:
        print("\nChecking deployments...")
        response = requests.get(deployments_url, headers=headers)
        
        if response.status_code == 200:
            deployments = response.json()
            print("\nAvailable Deployments:")
            print("-" * 30)
            
            if 'data' in deployments:
                for deployment in deployments['data']:
                    print(f"\nDeployment Name: {deployment.get('id', 'N/A')}")
                    print(f"  Model: {deployment.get('model', 'N/A')}")
                    print(f"  Status: {deployment.get('status', 'N/A')}")
                    
                    # Get more details about capabilities
                    if 'sku' in deployment:
                        print(f"  SKU: {deployment['sku'].get('name', 'N/A')}")
                        print(f"  Capacity: {deployment['sku'].get('capacity', 'N/A')}")
            else:
                print("No deployments found or unexpected response format")
                print(f"Response: {json.dumps(deployments, indent=2)}")
                
        elif response.status_code == 401:
            print("\n❌ Authentication failed. Please check your API key.")
        elif response.status_code == 404:
            print("\n❌ Endpoint not found. Please check your endpoint URL.")
        else:
            print(f"\n❌ Error: {response.status_code}")
            print(f"Response: {response.text}")
            
    except requests.exceptions.RequestException as e:
        print(f"\n❌ Connection error: {e}")
        print("\nTroubleshooting tips:")
        print("1. Check if your endpoint URL is correct")
        print("2. Ensure you have network connectivity")
        print("3. Verify the endpoint includes 'https://' prefix")
    
    # Try to check available models
    print("\n" + "=" * 50)
    print("Testing a simple completion...")
    
    # Common deployment names to try
    common_deployments = [
        "gpt-35-turbo",
        "gpt-4",
        "gpt-4-turbo",
        "gpt-35-turbo-16k",
        "text-davinci-003"
    ]
    
    for deployment_name in common_deployments:
        test_url = f"{endpoint}/openai/deployments/{deployment_name}/chat/completions?api-version={api_version}"
        
        test_payload = {
            "messages": [
                {"role": "system", "content": "You are a helpful assistant."},
                {"role": "user", "content": "Say 'Hello, I'm working!' in 5 words or less."}
            ],
            "max_tokens": 10,
            "temperature": 0
        }
        
        try:
            response = requests.post(test_url, headers=headers, json=test_payload)
            if response.status_code == 200:
                print(f"\n✅ Deployment '{deployment_name}' is working!")
                result = response.json()
                if 'choices' in result and len(result['choices']) > 0:
                    print(f"   Response: {result['choices'][0]['message']['content']}")
                break
            elif response.status_code == 404:
                continue  # Try next deployment name
        except:
            continue
    
    print("\n" + "=" * 50)
    print("\nTo use these models in automation:")
    print("1. Note down your working deployment name")
    print("2. Set environment variables:")
    print("   export AZURE_OPENAI_KEY='your-key'")
    print("   export AZURE_OPENAI_ENDPOINT='your-endpoint'")
    print("   export AZURE_OPENAI_DEPLOYMENT='your-deployment-name'")
    print("3. Run the automation script")

if __name__ == "__main__":
    check_azure_openai_models()