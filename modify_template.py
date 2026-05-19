import json

with open('new_template.json', 'r') as f:
    workflow = json.load(f)

nodes = workflow['nodes']
connections = workflow['connections']

# 1. Keep "On form submission" and "HTTP Request" untouched.
# 2. Keep Gemini Extractor untouched: "Information Extractor", "Google Gemini Chat Model"
# 3. Keep "Filter", "If", "No Operation, do nothing", "Append row in sheet" untouched.
# 4. Remove Email sending related nodes.
nodes_to_remove = [
    "Send a message",
    "Information Extractor1",
    "OpenAI Chat Model",
    "Append or update row in sheet",
    "Edit Fields1",
    "Loop Over Items",
    "Wait"
]

nodes = [n for n in nodes if n['name'] not in nodes_to_remove]

# 5. Create "Parse & Filter Apify" node to sit between "HTTP Request" and "Filter"
parse_apify_code = """
const items = $input.all();
const formType = $('On form submission').first().json["Business Type"] || 'general';

const qualifiedLeads = [];

const results = Array.isArray(items[0].json) ? items[0].json : items.map(i => i.json);

for (const place of results) {
  const rating = place.totalScore || 0;
  const reviews = place.reviewsCount || 0;

  if (rating >= 3.0 && reviews > 80) {
    const website = place.website || '';
    const phone = place.phoneUnformatted || place.phone || '';

    qualifiedLeads.push({
      json: {
        title: place.title || '',
        address: place.address || '',
        categoryName: formType.toLowerCase(),
        phoneUnformatted: phone,
        website: website,
        rating: rating,
        reviewsCount: reviews
      }
    });
  }
}

return qualifiedLeads;
"""

parse_node = {
  "parameters": {
    "jsCode": parse_apify_code
  },
  "id": "parse-apify-id",
  "name": "Parse & Filter Apify",
  "type": "n8n-nodes-base.code",
  "typeVersion": 2,
  "position": [
    -1456,
    112
  ],
  "alwaysOutputData": True
}

nodes.append(parse_node)

workflow['nodes'] = nodes

# Remove connections originating from deleted nodes
for key in nodes_to_remove:
    if key in connections:
        del connections[key]

# Also remove references to deleted nodes in the "Append row in sheet" main connections
if "Append row in sheet" in connections:
    # It was connecting to "Loop Over Items"
    del connections["Append row in sheet"]

# Remove references from "If" (which had a branch to deleted nodes maybe?)
# Actually "If" branches to "Append row in sheet" (kept) and "No Operation, do nothing" (kept). This is fine.

# 6. Update Connections:
# HTTP Request -> Parse & Filter Apify -> Filter
connections["On form submission"] = {
    "main": [
        [
            {
                "node": "HTTP Request",
                "type": "main",
                "index": 0
            }
        ]
    ]
}

connections["HTTP Request"] = {
    "main": [
        [
            {
                "node": "Parse & Filter Apify",
                "type": "main",
                "index": 0
            }
        ]
    ]
}

connections["Parse & Filter Apify"] = {
    "main": [
        [
            {
                "node": "Filter",
                "type": "main",
                "index": 0
            }
        ]
    ]
}

workflow['connections'] = connections

with open('modified_new_template.json', 'w') as f:
    json.dump(workflow, f, indent=2)
