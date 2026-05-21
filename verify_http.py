import json

with open('modified_new_template.json', 'r') as f:
    workflow = json.load(f)

for node in workflow['nodes']:
    if node['name'] == "HTTP Request":
        # Ensure it's exactly as they provided, with no rogue query params
        # Also ensure method is POST
        node['parameters']['method'] = "POST"
        node['parameters']['url'] = "=Apify_Actor_Endpoint_URL"
        node['parameters']['sendQuery'] = False # We don't need sendQuery because the token is in the URL
        if 'queryParameters' in node['parameters']:
            del node['parameters']['queryParameters']

        # Keep options for timeout
        node['parameters']['options'] = {
            "timeout": 900000
        }

with open('final_verified_template.json', 'w') as f:
    json.dump(workflow, f, indent=2)