#!/usr/bin/env python3
"""
Test Azure OpenAI connection with actual deployment
"""

import os
import requests
import json
from dotenv import load_dotenv

# Load environment variables
load_dotenv()

def test_azure_openai():
    """Test connection to Azure OpenAI"""
    
    api_key = os.getenv('AZURE_OPENAI_KEY')
    # Note: The endpoint should be specific to your resource
    endpoint = os.getenv('AZURE_OPENAI_ENDPOINT')
    deployment = os.getenv('AZURE_OPENAI_DEPLOYMENT', 'gpt-4o-mini')
    api_version = "2024-12-01-preview"  # Required for o1/o4 models
    
    print(f"Testing Azure OpenAI Connection")
    print("=" * 50)
    print(f"Endpoint: {endpoint}")
    print(f"Deployment: {deployment}")
    print(f"API Version: {api_version}")
    print("=" * 50)
    
    # Test each available deployment
    deployments = ["gpt-4o-mini", "gpt-4", "gpt-41", "gpt-4o", "o4-mini"]
    
    for deployment_name in deployments:
        print(f"\nTesting deployment: {deployment_name}")
        
        url = f"{endpoint}openai/deployments/{deployment_name}/chat/completions?api-version={api_version}"
        
        headers = {
            "api-key": api_key,
            "Content-Type": "application/json"
        }
        
        payload = {
            "messages": [
                {
                    "role": "system",
                    "content": "You are a helpful assistant. Respond concisely."
                },
                {
                    "role": "user",
                    "content": "What model are you and what's your token limit? Reply in one sentence."
                }
            ],
            "max_tokens": 100,
            "temperature": 0
        }
        
        try:
            response = requests.post(url, headers=headers, json=payload, timeout=10)
            
            if response.status_code == 200:
                result = response.json()
                content = result['choices'][0]['message']['content']
                usage = result.get('usage', {})
                
                print(f"✅ Success!")
                print(f"   Response: {content}")
                print(f"   Tokens used: {usage.get('total_tokens', 'N/A')}")
                
                # Get model details from response
                if 'model' in result:
                    print(f"   Model: {result['model']}")
                    
            else:
                print(f"❌ Failed: {response.status_code}")
                error_detail = response.json() if response.text else response.text
                print(f"   Error: {error_detail}")
                
        except Exception as e:
            print(f"❌ Exception: {e}")
    
    print("\n" + "=" * 50)
    print("Summary of Available Models:")
    print("-" * 30)
    print("• gpt-4o-mini: Fast, cost-effective for most tasks")
    print("• gpt-4: High capability, good for complex reasoning")
    print("• gpt-41: Latest GPT-4 version")
    print("• gpt-4o: Optimized GPT-4 variant")
    print("• o4-mini: Alternative mini model")
    
    print("\nRecommended for LeetCode automation:")
    print("→ gpt-4o-mini for fast generation")
    print("→ gpt-4 for complex problems")

if __name__ == "__main__":
    test_azure_openai()